//
// Created by root on 8/1/21.
//

#include "include/fixed_size_allocator.h"
#include <assert.h>
#include <algorithm>

void *FixedSizeAllocator::allocate(std::size_t size) {
    auto p = last_active_chunk_->allocate(size);
    if (p == nullptr) {
        last_active_chunk_ = &chunks_.emplace_back(block_size_, num_of_blocks_);
        p = last_active_chunk_->allocate(size);
    }
    return p;
}

void FixedSizeAllocator::deallocate(void *p, std::size_t size) {
    if (last_active_chunk_->has(p, block_size_, num_of_blocks_)) {
        last_active_chunk_->deallocate(p, size);
    } else {
        auto it = std::find_if(chunks_.begin(), chunks_.end(),
                               [p, this](const Chunk &chunk) { return chunk.has(p, block_size_, num_of_blocks_); });
        assert(it!=chunks_.end());
        it->deallocate(p, size);
        last_active_chunk_ = &(*it);
    }
}
