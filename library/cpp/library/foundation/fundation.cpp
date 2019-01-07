//Don't change this file manually, it was generated by automation tool.

#include "fundation.h"
#include "bridge.h"

struct FDN_Logger_Shell : FDN::Logger {
    const int _coreID;
    FDN_Logger_Shell(int coreID);
    ~FDN_Logger_Shell();
    void print(const std::string &text);
};

std::shared_ptr<FDN::Logger> FDN::Logger::infoHandler() {
    BRGCallMethod(100, 1, 0);
    int retID = BRGParam<int>::read();
    std::shared_ptr<FDN::Logger> ret = BRGReleaseCoreFromID<FDN_Logger_Shell>(100, retID);
    BRGPop(1);
    return ret;
}

std::shared_ptr<FDN::Logger> FDN::Logger::errorHandler() {
    BRGCallMethod(100, 2, 0);
    int retID = BRGParam<int>::read();
    std::shared_ptr<FDN::Logger> ret = BRGReleaseCoreFromID<FDN_Logger_Shell>(100, retID);
    BRGPop(1);
    return ret;
}

FDN_Logger_Shell::FDN_Logger_Shell(int coreID): _coreID(coreID) {
    BRGRetainCore(100, _coreID);
}

FDN_Logger_Shell::~FDN_Logger_Shell() {
    BRGReleaseCore(100, _coreID);
}

void FDN_Logger_Shell::print(const std::string &text) {
    BRGPush();
    BRGParam<std::string>::write(text);
    BRGCallMethod(100, 3, _coreID);
    BRGPop(1);
}
