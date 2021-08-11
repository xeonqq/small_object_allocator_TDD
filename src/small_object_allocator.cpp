//
// Created by root on 8/8/21.
//
#include "include/small_object_allocator.h"
#include <algorithm>
#include <assert.h>

SmallObjectAllocator::SmallObjectAllocator(size_t num_blocks_per_chunk) : num_blocks_per_chunk_{num_blocks_per_chunk},
                                                                          last_alloc_{nullptr},
                                                                          last_dealloc_{nullptr} {}

void *SmallObjectAllocator::allocate(std::size_t size) {
    void *p;
    if (last_alloc_ && last_alloc_->block_size()==size) {
        p=last_alloc_->allocate(size);
    } else {
        auto it = find_matching_fixed_size_allocator(size);
        if (it == fixed_size_allocators_.end()) {
            fixed_size_allocators_.emplace_back(size, num_blocks_per_chunk_);
            last_alloc_ = &fixed_size_allocators_.back();
            p = last_alloc_->allocate(size);
            last_dealloc_ = last_alloc_;
        } else {
            p = it->allocate(size);
            last_alloc_ = &(*it);
        }
    }
    return p;
}

void SmallObjectAllocator::deallocate(void *p, size_t size) {
    if (!last_dealloc_ || last_dealloc_->block_size()!=size) {
        auto it = find_matching_fixed_size_allocator(size);
        assert(it != fixed_size_allocators_.end());
        last_dealloc_ = &(*it);
    }
    last_dealloc_->deallocate(p, size);
}

std::vector<FixedSizeAllocator>::iterator SmallObjectAllocator::find_matching_fixed_size_allocator(size_t size) {
    auto it = std::find_if(fixed_size_allocators_.begin(), fixed_size_allocators_.end(),
                           [size](const FixedSizeAllocator &allocator) {
                               return allocator.block_size() == size;
                           });
    return it;
}


