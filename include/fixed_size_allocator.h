#include <stdlib.h>
#include <cstddef>
#include <vector>
#include "chunk.h"

class FixedSizeAllocator
{
  public:
  FixedSizeAllocator(size_t chunk_size, size_t num_of_chunks):
    chunk_size_{chunk_size}, num_of_chunks_{num_of_chunks} {
    chunks_.emplace_back(chunk_size_, num_of_chunks_);
    last_active_chunk_ = &chunks_.back();
    last_allocated_chunk_idx_ = chunks_.size();
    last_deallocated_chunk_idx_ = chunks_.size();
    }
  void* allocate(std::size_t size);
  void deallocate(void* p, std::size_t size);
  size_t chunk_size() const  {return chunk_size_;}

  private:
  size_t chunk_size_;
  size_t num_of_chunks_;
  std::vector<Chunk> chunks_;
  Chunk* last_active_chunk_;
  size_t last_allocated_chunk_idx_;
  size_t last_deallocated_chunk_idx_;
};


