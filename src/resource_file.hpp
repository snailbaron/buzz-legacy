#ifndef _RESOURCE_FILE_HPP_
#define _RESOURCE_FILE_HPP_

#include "resource.hpp"

class ResourceFile
{
public:
    virtual bool Open() = 0;
    virtual int GetResourceSize(const Resource &r) = 0;
    virtual int GetResource(const Resource &r, char *buffer) = 0;
    virtual ~ResourceFile() {}
};

#endif
