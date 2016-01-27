#ifndef _BASE_PROCESS_HPP_
#define _BASE_PROCESS_HPP_

#include <memory>

enum class ProcessState
{
    New,        // new process: initializes and goes to Running state
    Running,    // running process: must be updated
    Paused,     // paused process: not updated
    Dead        // dead process: must be removed, next process spawns if exists
};

/** Base class for process */
class BaseProcess
{
public:
    BaseProcess();
    virtual ~BaseProcess();

    bool IsActive() const { return (m_state == ProcessState::New || m_state == ProcessState::Running); }
    bool IsNew() const { return (m_state == ProcessState::New); }
    bool IsDead() const { return (m_state == ProcessState::Dead); }

    /* Simple getters and setters */
    const ProcessState & State() const { return m_state; }
    void SetState(const ProcessState &state) { m_state = state; }
    std::shared_ptr<BaseProcess> Next() const { return m_next; }
    
    /* Chaining processes into sequence */
    std::shared_ptr<BaseProcess> SetNext(std::shared_ptr<BaseProcess> next);

    /* Interface for child classes */
    virtual void Init() {}
    virtual void Update(long deltaMs) {}
    virtual void Kill() {}

private:
    ProcessState m_state;
    std::shared_ptr<BaseProcess> m_next;
};

#endif
