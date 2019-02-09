//

@interface CQBus : NSObject

//NOTE: these static member designed for thread safe.

+ (void)post:(NSString *)name param:(NSObject *)param;
+ (void)addObserver:(NSObject *)observer selector:(SEL)selector name:(NSString *)name;

//it's not necessary to remove a obserser by "removeObserver:" method.
//CQBus save the weak reference of observer.
+ (void)removeObserver:(NSObject *)observer;

@end