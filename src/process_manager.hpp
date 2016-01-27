#ifndef _PROCESS_MANAGER_HPP_
#define _PROCESS_MANAGER_HPP_

#include <list>
#include "process.hpp"

typedef std::list<std::shared_ptr<Process>> ProcessList;

class ProcessManager
{
public:
    ~ProcessManager();

    void Attach(std::shared_ptr<Process> process);

    bool HasProcesses();
    bool IsProcessActive(int type);

    void UpdateProcesses(int deltaMs);

protected:
    ProcessList m_processList;

private:
    void Detach(std::shared_ptr<Process> process);
};

#endif
