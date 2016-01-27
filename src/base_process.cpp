#include "base_process.hpp"

BaseProcess::BaseProcess() :
    m_state(ProcessState::New),
    m_next()
{
}

BaseProcess::~BaseProcess()
{
}

std::shared_ptr<BaseProcess> BaseProcess::SetNext(std::shared_ptr<BaseProcess> next)
{
    m_next = next;
    return next;
}
