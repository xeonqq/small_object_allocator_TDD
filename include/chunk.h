#ifndef SMALL_OBJECT_ALLOCATOR_CHUNK_H
#define SMALL_OBJECT_ALLOCATOR_CHUNK_H
#include <stdlib.h>
#include <cstddef>
#include <memory>

class Chunk{
  public:
    Chunk(size_t block_size, unsigned char num_of_blocks);
    void* allocate(size_t size);
    void deallocate(void* p, size_t size);
    bool has(void *p, size_t block_size, size_t num_of_blocks) const;
    bool full() const;
    bool empty(size_t num_of_blocks) const;

  private:
    std::unique_ptr<unsigned char[]> data_;
    unsigned char current_idx_;
    unsigned char available_chunks_;

};

#endif