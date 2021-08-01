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
    bool in_chunk = chunks_[last_deallocated_chunk_idx_].in(static_cast<unsigned char*>(p), num_of_chunks_);
    if (!in_chunk)
    {
        for (size_t i{0}; i<chunks_.size(); ++i)
        {
            if (chunks_[i].in(static_cast<unsigned char*>(p), num_of_chunks_))
            {
                last_allocated_chunk_idx_ = i;
                break;
            }
        }
    }
    chunks_[last_allocated_chunk_idx_].deallocate(static_cast<unsigned char*>(p), size);
    if (chunks_[last_deallocated_chunk_idx_].full())
    {

    }

}
