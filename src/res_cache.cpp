#include "res_cache.hpp"

ResCache::ResCache(const unsigned int sizeMb, ResourceFile *resFile) :
    m_cacheSize(sizeMb * 1024 * 1024),
    m_allocated(0),
    m_file(resFile)
{
}

ResCache::~ResCache()
{
    while (!m_lru.empty()) {
        FreeOneResource();
    }
    // TODO: SAFE_DELETE(m_file)
}

std::shared_ptr<ResHandle> ResCache::GetHandle(Resource *r)
{
    std::shared_ptr<ResHandle> handle = Find(r);
    if (handle == NULL) {
        handle = Load(r);
    } else {
        Update(handle);
    }
    return handle;
}

std::shared_ptr<ResHandle> ResCache::Find(Resource *r)
{
    return m_resources[r->name];
}

const void * ResCache::Update(std::shared_ptr<ResHandle> handle)
{
    // TODO: Remove handle from m_lru, and promote to front
}

void ResCache::Free(std::shared_ptr<ResHandle> handle)
{
    // TODO: Find resource by handle, remove from cache
}

std::shared_ptr<ResHandle> ResCache::Load(Resource *r)
{
    int size = m_file->GetResourceSize(*r);
    char *buffer = Allocate(size);
    if (buffer == NULL) {
        // Cache is out of memory
        return std::shared_ptr<ResHandle>();
    }

    std::shared_ptr<ResHandle> handle(r->CreateHandle(buffer, size, this));
    handle->Load(m_file);

    m_lru.push_front(handle);
    m_resources[r->name] = handle;

    return handle;
}

char * ResCache::Allocate(unsigned int size)
{
    if (!MakeRoom(size)) {
        return NULL;
    }

    char *mem = new char[size];
    if (mem) {
        m_allocated += size;
    }

    return mem;
}

bool ResCache::MakeRoom(unsigned int size)
{
    if (size > m_cacheSize) {
        return false;
    }

    while (size > m_cacheSize - m_allocated) {
        if (m_lru.empty()) {
            return false;
        }
        FreeOneResource();
    }

    return true;
}

void ResCache::FreeOneResource()
{
    ResHandleList::iterator last = m_lru.end();
    last--;
    std::shared_ptr<ResHandle> handle = *last;
    m_lru.pop_back();
    m_resources.erase(handle->GetResource().name);
}