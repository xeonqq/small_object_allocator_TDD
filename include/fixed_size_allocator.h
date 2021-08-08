
#ifndef SMALL_OBJECT_ALLOCATOR_FIXED_SIZE_ALLOCATOR_H
#define SMALL_OBJECT_ALLOCATOR_FIXED_SIZE_ALLOCATOR_H
#include <stdlib.h>
#include <cstddef>
#include <vector>
#include "chunk.h"

class FixedSizeAllocator {
public:
    FixedSizeAllocator(size_t block_size, size_t num_of_blocks) :
            block_size_{block_size}, num_of_blocks_{num_of_blocks} {
        chunks_.emplace_back(block_size_, num_of_blocks_);
        alloc_chunk_ = &chunks_.back();
        dealloc_chunk_ = alloc_chunk_;
    }

    void *allocate(std::size_t size);

    void deallocate(void *p, std::size_t size);

    size_t block_size() const { return block_size_; }

    size_t number_of_chunks() const { return chunks_.size(); }

private:
    bool has_already_one_chunk_empty() const;

private:
    size_t block_size_;
    size_t num_of_blocks_;
    std::vector<Chunk> chunks_;
    Chunk *alloc_chunk_;
    Chunk *dealloc_chunk_;

};

#endif // SMALL_OBJECT_ALLOCATOR_FIXED_SIZE_ALLOCATOR
