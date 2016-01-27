#include "process.hpp"

inline void Process::OnUpdate(const int deltaMs)
{
    if (m_initialUpdate) {
        OnInitialize();
        m_initialUpdate = false;
    }
}