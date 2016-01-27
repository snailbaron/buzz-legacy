#include "process_manager.hpp"

void ProcessManager::UpdateProcesses(int deltaMs)
{
    for (ProcessList::iterator i = m_processList.begin(); i != m_processList.end(); ++i) {
        std::shared_ptr<Process> p(*i);
        if (p->IsDead()) {
            std::shared_ptr<Process> next = p->GetNext();
            if (next) {
                p->SetNext(std::shared_ptr<Process>(nullptr));
                Attach(next);
            }
            Detach(p);
        } else if (p->IsActive() && !p->IsPaused()) {
            p->OnUpdate(deltaMs);
        }
        ++i;
    }
}