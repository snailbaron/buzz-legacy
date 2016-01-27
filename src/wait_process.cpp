#include "wait_process.hpp"

WaitProcess::WaitProcess(Process *parent, unsigned int ms) :
    Process(PROC_WAIT, 0),  // parent?
    m_start(0),
    m_stop(ms)
{
}

void WaitProcess::OnUpdate(const int deltaMs)
{
    Process::OnUpdate(deltaMs);
    if (m_active) {
        m_start += deltaMs;
        if (m_start >= m_stop) {
            Kill();
        }
    }
}