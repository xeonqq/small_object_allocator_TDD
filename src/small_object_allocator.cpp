//
// Created by root on 8/8/21.
//
#include "include/small_object_allocator.h"
#include <algorithm>
#include <assert.h>

SmallObjectAllocator::SmallObjectAllocator(size_t num_blocks_per_chunk):num_blocks_per_chunk_{num_blocks_per_chunk}{}

void* SmallObjectAllocator::allocate(std::size_t size){

    auto it = find_matching_fixed_size_allocator(size);
    void* p;
    if (it==fixed_size_allocators_.end())
    {
        auto& fs_allocator =fixed_size_allocators_.emplace_back(size, num_blocks_per_chunk_);
        p=fs_allocator.allocate(size);
    }
    else{
        p=it->allocate(size);
    }
    return p;
}

void SmallObjectAllocator::deallocate(void *p, size_t size) {
    auto it = find_matching_fixed_size_allocator(size);
    assert(it != fixed_size_allocators_.end());
    it->deallocate(p, size);
}

std::vector<FixedSizeAllocator>::iterator SmallObjectAllocator::find_matching_fixed_size_allocator(size_t size) {
    auto it = std::find_if(fixed_size_allocators_.begin(), fixed_size_allocators_.end(), [size](const FixedSizeAllocator& allocator){
        return allocator.block_size() == size;
    });
    return it;
}


