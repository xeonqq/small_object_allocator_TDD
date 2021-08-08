//
// Created by root on 8/8/21.
//

#ifndef SMALL_OBJECT_ALLOCATOR_SINGLETON_H
#define SMALL_OBJECT_ALLOCATOR_SINGLETON_H
#include <memory>
template<typename T>
class Singleton{
public:
    static T& get_instance() {
        static std::unique_ptr<T> singleton;
        if (!singleton){
            singleton = std::make_unique<T>();
        }
        return *singleton.get();

    }
private:
    Singleton()=delete;

};
#endif //SMALL_OBJECT_ALLOCATOR_SINGLETON_H
