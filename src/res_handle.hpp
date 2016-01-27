#ifndef _RES_HANDLE_HPP_
#define _RES_HANDLE_HPP_

#include "resource.hpp"
#include "resource_file.hpp"

class ResHandle
{
    // friend class ResCache?

public:
    ResHandle(Resource &resource, char *buffer, unsigned int size, ResCache *cache);
    virtual ~ResHandle();

    virtual int Load(ResourceFile *file) { return file->GetResource(m_resource, m_buffer); }
    unsigned int Size() const { return m_size; }
    char * Buffer() const { return m_buffer; }

    Resource GetResource() { return m_resource; }

protected:
    Resource m_resource;
    char *m_buffer;
    unsigned int m_size;
    ResCache *m_cache;
};

#endif
