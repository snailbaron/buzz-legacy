#ifndef _RES_CACHE_HPP_
#define _RES_CACHE_HPP_

#include <list>
#include <map>
#include <string>
#include <memory>
#include "res_handle.hpp"
#include "resource.hpp"
#include "resource_file.hpp"

typedef std::list<std::shared_ptr<ResHandle>> ResHandleList;
typedef std::map<std::string, std::shared_ptr<ResHandle>> ResHandleMap;

class ResCache
{
public:
    ResCache(const unsigned int sizeMb, ResourceFile *resFile);
    ~ResCache();

    bool Init() { return m_file->Open(); }
    std::shared_ptr<ResHandle> GetHandle(Resource *r);
    void Flush();

protected:
    // List of resource handles, in least-recently-used order
    ResHandleList m_lru;

    // Resource handle map for resource lookup
    ResHandleMap m_resources;

    ResourceFile *m_file;

    unsigned int m_cacheSize;       // total memory size for cache
    unsigned int m_allocated;       // amount of memory allocated

    std::shared_ptr<ResHandle> Find(Resource *r);
    const void * Update(std::shared_ptr<ResHandle> handle);
    std::shared_ptr<ResHandle> Load(Resource *r);
    void Free(std::shared_ptr<ResHandle> handle);

    bool MakeRoom(unsigned int size);
    char * Allocate(unsigned int size);
    void FreeOneResource();
    void MemoryHasBeenFreed(unsigned int size);
    
};


#endif
