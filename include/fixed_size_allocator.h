#include <stdlib.h>
#include <cstddef>
#include <vector>
#include "chunk.h"

class FixedSizeAllocator
{
  public:
  FixedSizeAllocator(size_t block_size, size_t num_of_blocks):
    block_size_{block_size}, num_of_blocks_{num_of_blocks} {
    chunks_.emplace_back(block_size_, num_of_blocks_);
    last_active_chunk_ = &chunks_.back();
    last_allocated_chunk_idx_ = chunks_.size();
    last_deallocated_chunk_idx_ = chunks_.size();
    }
  void* allocate(std::size_t size);
  void deallocate(void* p, std::size_t size);
  size_t block_size() const  {return block_size_;}

  private:
  size_t block_size_;
  size_t num_of_blocks_;
  std::vector<Chunk> chunks_;
  Chunk* last_active_chunk_;
  size_t last_allocated_chunk_idx_;
  size_t last_deallocated_chunk_idx_;
};


