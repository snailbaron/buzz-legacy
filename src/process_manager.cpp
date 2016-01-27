#include "process_manager.hpp"

void ProcessManager::UpdateProcesses(long deltaMs)
{
    std::list<std::shared_ptr<BaseProcess>>::iterator i = m_processes.begin();
    while (i != m_processes.end()) {
        if ((*i)->IsDead()) {
            // Remove process from list, and activate next one
            std::shared_ptr<BaseProcess> next = (*i)->Next();
            if (next) {
                (*i)->SetNext(nullptr);
                m_processes.push_back(next);
            }
            i = m_processes.erase(i);
        } else if ((*i)->IsActive()) {
            if ((*i)->IsNew()) {
                (*i)->Init();
                (*i)->SetState(ProcessState::Running);
            }
            (*i)->Update(deltaMs);
            i++;
        }
    }
}