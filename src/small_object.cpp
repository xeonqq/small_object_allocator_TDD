//
// Created by root on 7/27/21.
//

#include <iostream>
#include "include/small_object.h"
#include "include/singleton.h"
#include "include/small_object_allocator.h"

void* SmallObject::operator new(std::size_t size)
{
    auto& allocator = Singleton<SmallObjectAllocator>::get_instance(255);
    auto p = allocator.allocate(size);
//    std::cout << "allocated: " << size <<" @ " << p <<  std::endl;
    return p;
}

void SmallObject::operator delete (void* p, std::size_t size)
{
//    std::cerr << "deallocate: " << p << std::endl;
    auto& allocator = Singleton<SmallObjectAllocator>::get_instance(255);
    allocator.deallocate(p, size);
}
