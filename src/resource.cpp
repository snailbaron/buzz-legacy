#include "resource.hpp"

ResHandle * Resource::CreateHandle(const char *buffer, unsigned int size, ResCache *cache)
{
    return new ResHandle(*this, (char *)buffer, size, cache);
}