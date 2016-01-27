#ifndef _WAIT_PROCESS_HPP_
#define _WAIT_PROCESS_HPP_

#include "process.hpp"

class WaitProcess : public Process
{
public:
    WaitProcess(Process *parent, unsigned int ms);

    virtual void OnUpdate(const int deltaMs);

protected:
    unsigned int m_start;
    unsigned int m_stop;
};

#endif
