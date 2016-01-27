#ifndef _PROCESS_MANAGER_HPP_
#define _PROCESS_MANAGER_HPP_

#include <list>
#include <memory>
#include "base_process.hpp"

class ProcessManager
{
public:
    void UpdateProcesses(long deltaMs);

protected:
    std::list<std::shared_ptr<BaseProcess>> m_processes;
};

#endif
