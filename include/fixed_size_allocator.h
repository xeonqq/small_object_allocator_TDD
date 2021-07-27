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
  size_t last_allocated_chunk_idx_;
  size_t last_deallocated_chunk_idx_;
};

void* FixedSizeAllocator::allocate(std::size_t size)
{
  void* p = chunks_[last_allocated_chunk_idx_].allocate(size);
  if (p==nullptr)
  {
    for (size_t i{0};i<chunks_.size();++i)
    {
      if (!chunks_[i].empty())
      {
        last_allocated_chunk_idx_ = i;
        break;
      }
    }

    //start using the last available chunk
    if (last_allocated_chunk_idx_ == chunks_.size())
    {
      chunks_.emplace_back(chunk_size_, num_of_chunks_);
    }
    
    p = chunks_[last_allocated_chunk_idx_].allocate(size);
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
  if (chunks_[last_deallocated_chunk_idx_].empty())
  {

  }

}
