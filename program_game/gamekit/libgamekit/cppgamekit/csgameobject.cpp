#include "csgameobject.hh"
#include "cscodebehaviour.hh"

//global data:

static std::map<void *, csGameObjectRef> sActiveRoots;
static std::map<void *, csGameObjectRef> sGlobalRoots;

//game object:

cq_member(csGameObject) {
    std::string name;
    
    csGameObjectWeakRef parent;
    std::vector<csGameObjectRef> children;
    
    std::map<cqClass *, csCodeBehaviourRef> codeBehaviours;
    std::map<cqClass *, csComponentRef> components;
};

//create and destroy:

const std::map<void *, csGameObjectRef> &csGameObject::activeRoots() {
    return sActiveRoots;
}

const std::map<void *, csGameObjectRef> &csGameObject::globalRoots() {
    return sGlobalRoots;
}

csGameObjectRef csGameObject::createWithName(const std::string &name) {
    
    //create new game object:
    csGameObjectRef gameObject = csGameObject::create();
    gameObject->setName(name);
    gameObject->addComponent(csTransform::clazz());
    
    //add to active scene:
    void *key = gameObject.get();
    sActiveRoots[key] = gameObject;
    
    return gameObject;
}

void csGameObject::dontDestoryOnLoad(csGameObjectRef gameObject) {
    if (gameObject == nullptr) {
        return;
    }
    
    //NOTE: only root game object can be keep after load other scene.
    if (gameObject->parent() != nullptr) {
        return;
    }
    
    void *key = gameObject.get();
    sActiveRoots.erase(key);
    sGlobalRoots[key] = gameObject;
}

void csGameObject::destroyActiveRoots() {
    std::map<void *, csGameObjectRef> gameObjects = sActiveRoots;
    for (auto &cp : gameObjects) {
        cp.second->emitDestroy();
    }
    sActiveRoots.clear();
}

void csGameObject::destroy(csGameObjectRef gameObject) {
    if (gameObject == nullptr) {
        return;
    }
    
    gameObject->emitDestroy();
    
    void *key = gameObject.get();
    if (cqMap::contains(sActiveRoots, key)) {
        
        //remove from active roots.
        sActiveRoots.erase(key);
        
    } else if (cqMap::contains(sGlobalRoots, key)) {
        
        //remove from global roots.
        sGlobalRoots.erase(key);
        
    } else {
        
        //remove from parent.
        //NOTE: don't use setParent(null), it will move the game object to active roots.
        csGameObjectRef parent = gameObject->parent();
        auto brothers = parent->dat->children;
        std::remove_if(brothers.begin(), brothers.end(), [=](csGameObjectRef it) {
            return it.get() == key;
        });
    }
}

//properties:

void csGameObject::setName(const std::string &name) {
    dat->name = name;
}

std::string csGameObject::name() {
    return dat->name;
}

//hierarchy:

void csGameObject::setParent(csGameObjectRef parent) {
    csGameObjectRef oldParent = dat->parent.lock();
    
    if (oldParent == parent) {
        return;
    }
    
    //remove from old parent:
    if (oldParent != nullptr) {
        auto brothers = oldParent->dat->children;
        std::remove_if(brothers.begin(), brothers.end(), [=](csGameObjectRef it) {
            return it.get() == this;
        });
        dat->parent.reset();
    }
    
    //add to new parent or roots:
    if (parent != nullptr) {
        parent->dat->children.push_back(strongRef());
        dat->parent = parent;
    } else {
        sActiveRoots[this] = strongRef();
    }
}

csGameObjectRef csGameObject::parent() {
    return dat->parent.lock();
}

const std::vector<csGameObjectRef> &csGameObject::children() {
    return dat->children;
}

void csGameObject::detachChildren() {
    //move children to active roots.
    for (auto &it : dat->children) {
        sActiveRoots[it.get()] = it;
        it->dat->parent.reset();
    }
    dat->children.clear();
}

//components:

csComponentRef csGameObject::addComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return nullptr;
    }
    if (cqMap::contains(dat->codeBehaviours, clazz)) {
        return dat->codeBehaviours[clazz];
    }
    if (cqMap::contains(dat->components, clazz)) {
        return dat->components[clazz];
    }
    
    auto component = cqObject::cast<csComponent>(clazz->create());
    component->resetGameObjectIfNeeded(strongRef());
    
    if (clazz->isKindOfClass(csCodeBehaviour::clazz())) {
        //NOTE: put the code behaviour into list first.
        //such when awake() and start() called, they can find the object/component tree.
        auto code = cqObject::cast<csCodeBehaviour>(component);
        dat->codeBehaviours[clazz] = code;
    } else {
        dat->components[clazz] = component;
    }
    
    return component;
}

void csGameObject::removeComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return;
    }
    
    if (cqMap::contains(dat->codeBehaviours, clazz)) {
        csCodeBehaviourRef codeBehaviour = dat->codeBehaviours[clazz];
        codeBehaviour->emitDestroy();
        dat->codeBehaviours.erase(clazz);
    } else {
        dat->components.erase(clazz);
    }
}

csComponentRef csGameObject::getComponent(cqClass *clazz) {
    if (clazz == nullptr) {
        return nullptr;
    }
    
    if (cqMap::contains(dat->codeBehaviours, clazz)) {
        return dat->codeBehaviours[clazz];
    } else if (cqMap::contains(dat->components, clazz)) {
        return dat->components[clazz];
    } else {
        return nullptr;
    }
}

csTransformRef csGameObject::transform() {
    return getComponent<csTransform>();
}

void csGameObject::emitUpdate() {
    
    //NOTE: it's possibly to destroy a code behaviour in update(),
    //keep the traversed container unchanged.
    std::map<cqClass *, csCodeBehaviourRef> codes = dat->codeBehaviours;
    for (auto &cp : codes) {
        cp.second->emitUpdate();
    }
}

void csGameObject::emitDestroy() {
    
    //call children:
    std::vector<csGameObjectRef> children = dat->children;
    for (auto &it : children) {
        it->emitDestroy();
    }
    
    //call own code behaviours:
    std::map<cqClass *, csCodeBehaviourRef> codes = dat->codeBehaviours;
    for (auto &cp : codes) {
        cp.second->emitDestroy();
    }
}
