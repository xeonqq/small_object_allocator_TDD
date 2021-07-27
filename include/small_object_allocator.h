#include <stdlib.h>
#include <cstddef>
#include <vector>
#include "fixed_size_allocator.h"

class SmallObjectAllocator
{
  public:
  void* allocate(std::size_t size);
  private:
  std::vector<FixedSizeAllocator> fixed_size_allocators_;
};

void* SmallObjectAllocator::allocate(std::size_t size){


}
