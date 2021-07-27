#include <stdlib.h>
#include <cstddef>
class SmallObject{
  public:
    void* operator new (std::size_t size);
    void operator new (std::size_t size);
};

void* SmallObject::operator new(std::size_t size)
{
}
