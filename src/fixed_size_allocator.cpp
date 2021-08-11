//
// Created by root on 8/1/21.
//

#include "include/fixed_size_allocator.h"
#include <assert.h>
#include <algorithm>
#include <algorithm>

void *FixedSizeAllocator::allocate(std::size_t size) {
    auto p = alloc_chunk_->allocate(size);
    if (p == nullptr) {
        auto it = std::find_if(chunks_.begin(), chunks_.end(),
                               [p, this](const Chunk &chunk) { return !chunk.full(); });
        if (it != chunks_.end()) {
            p = it->allocate(size);
            alloc_chunk_ = &(*it);
        } else {
            chunks_.emplace_back(block_size_, num_of_blocks_);
            alloc_chunk_ = &chunks_.back();
            dealloc_chunk_ = alloc_chunk_;
            p = alloc_chunk_->allocate(size);
        }
    }

    return p;
}

void FixedSizeAllocator::deallocate(void *p, std::size_t size) {
    if (dealloc_chunk_->has(p, block_size_, num_of_blocks_)) {
        dealloc_chunk_->deallocate(p, size);
    } else {
        auto it_forward=dealloc_chunk_;
        const auto* rend = (&chunks_.front())-1;
        const auto* end = &(chunks_.back())+1;
        while(true)
        {
            if (++it_forward!=end && it_forward->has(p, block_size_, num_of_blocks_))
            {
                dealloc_chunk_ = it_forward;
                break;
            }
            if (--dealloc_chunk_ != rend && dealloc_chunk_->has(p, block_size_, num_of_blocks_))
            {
                break;
            }
        }
        dealloc_chunk_->deallocate(p, size);
    }

    if (dealloc_chunk_->empty(num_of_blocks_)) {

        auto empty_chunk_it = chunks_.begin() + std::distance(chunks_.data(), dealloc_chunk_);

        if (has_already_one_chunk_empty()) {
            std::iter_swap(empty_chunk_it, chunks_.end() - 2);
            chunks_.erase(std::prev(chunks_.end()));
        } else {
            std::iter_swap(empty_chunk_it, std::prev(chunks_.end()));
        }
        alloc_chunk_ = &chunks_.back();
        dealloc_chunk_ = alloc_chunk_;
    }
}

bool FixedSizeAllocator::has_already_one_chunk_empty() const {
    return ((dealloc_chunk_ != &chunks_.back()) && (chunks_.back().empty(num_of_blocks_)));
}
