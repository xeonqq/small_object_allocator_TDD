#ifndef SMALL_OBJECT_ALLOCATOR_SMALL_OBJECT_ALLOCATOR_H
#define SMALL_OBJECT_ALLOCATOR_SMALL_OBJECT_ALLOCATOR_H
#include <stdlib.h>
#include <cstddef>
#include <vector>
#include "fixed_size_allocator.h"

class SmallObjectAllocator {
public:
    SmallObjectAllocator(size_t num_blocks_per_chunk);

    void *allocate(std::size_t size);

    void deallocate(void *p, size_t size);

    size_t num_of_fixed_size_allocators() const { return fixed_size_allocators_.size(); }

private:
    std::vector<FixedSizeAllocator>::iterator find_matching_fixed_size_allocator(size_t size);

private:
    std::vector<FixedSizeAllocator> fixed_size_allocators_;
    size_t num_blocks_per_chunk_;
    FixedSizeAllocator* last_alloc_;
    FixedSizeAllocator* last_dealloc_;

};


#endif