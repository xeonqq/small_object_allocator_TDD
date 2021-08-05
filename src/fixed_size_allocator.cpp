//
// Created by root on 8/1/21.
//

#include "include/fixed_size_allocator.h"

void* FixedSizeAllocator::allocate(std::size_t size)
{
    auto p = last_active_chunk_->allocate(size);
    if (p == nullptr)
    {
        last_active_chunk_ = &chunks_.emplace_back(chunk_size_, num_of_chunks_);
        p = last_active_chunk_->allocate(size);
    }
    return p;
}

void FixedSizeAllocator::deallocate(void* p, std::size_t size){
    last_active_chunk_->deallocate(p, size);
}
