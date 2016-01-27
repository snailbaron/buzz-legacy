#include "res_handle.hpp"

ResHandle::ResHandle(Resource &resource, char *buffer, unsigned int size, ResCache *cache) :
    m_resource(resource),
    m_buffer(buffer),
    m_size(size),
    m_cache(cache)
{
}

ResHandle::~ResHandle()
{
    if (m_buffer) {
        delete[] m_buffer;
    }
    m_cache->MemoryHasBeenFreed(m_size);
}