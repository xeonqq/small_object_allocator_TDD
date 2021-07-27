//
// Created by root on 7/27/21.
//

#include <iostream>
#include "include/small_object_malloc.h"

void* SmallObjectMalloc::operator new(std::size_t size)
{
    auto p =  malloc(size);
//    std::cerr << "allocated: " << size <<" @ " << p <<  std::endl;
    return p;
}

void SmallObjectMalloc::operator delete(void* p)
{
//    std::cerr << "deallocate: " << p << std::endl;
    free(p);
}
