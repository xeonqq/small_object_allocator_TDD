//
// Created by root on 7/27/21.
//

#ifndef SMALL_OBJECT_ALLOCATOR_SMALL_OBJECT_H
#define SMALL_OBJECT_ALLOCATOR_SMALL_OBJECT_H

#include <stdlib.h>
#include <cstddef>
class SmallObject{
public:
    void* operator new (std::size_t size);
    void operator delete (void* p);
};

#endif //SMALL_OBJECT_ALLOCATOR_SMALL_OBJECT_H
