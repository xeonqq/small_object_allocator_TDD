#include <stdlib.h>
#include <cstddef>
#include <memory>

class Chunk{
  public:
    Chunk(size_t chunk_size, unsigned char num_of_chunks);
    void* allocate(size_t size);
    void deallocate(void* p, size_t size);
    bool in(unsigned char* p, size_t num_of_chunks) const;
    bool full() const;

  private:
    std::unique_ptr<unsigned char[]> data_;
    unsigned char current_idx_;
    unsigned char available_chunks_;

};

