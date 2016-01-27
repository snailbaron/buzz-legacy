#ifndef _RESOURCE_HPP_
#define _RESOURCE_HPP_

#include <string>
#include "res_handle.hpp"
#include "res_cache.hpp"

struct Resource
{
    std::string name;
    Resource(std::string aname) : name(aname) {}
    virtual ResHandle * CreateHandle(const char *buffer, unsigned int size, ResCache *cache);
};

#endif
