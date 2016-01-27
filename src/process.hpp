#ifndef _PROCESS_HPP_
#define _PROCESS_HPP_

#include <memory>

#define PROC_WAIT 0

class Process
{
    // friend class ProcessManager?

public:
    Process(int type, unsigned int order = 0);
    virtual ~Process();

    bool IsDead() const { return m_kill; }
    int GetType() const { return m_type; }
    void SetType(const int type) { m_type = type; }
    bool IsActive() const { return m_active; }
    void SetActive(const bool active) { m_active = active; }
    bool IsAttached() const;
    void SetAttached(const bool attached);
    bool IsPaused() const { return m_paused; }
    bool IsInitialized() const { return !m_initialUpdate; }

    const std::shared_ptr<Process> GetNext() const { return m_next; }
    void SetNext(std::shared_ptr<Process> next);

    virtual void OnUpdate(const int deltaMs);
    virtual void OnInitialize() {};
    virtual void Kill();
    virtual void TogglePause() { m_paused = !m_paused; }

protected:
    int m_type;     // type of process running
    bool m_kill;    // tells ProcessManager to kill this process
    bool m_active;
    bool m_paused;
    bool m_initialUpdate;
    std::shared_ptr<Process> m_next;    // dependant process

private:
    unsigned int m_processFlags;

private:
    // Protect from copying
    Process(const Process &other);
    Process & operator=(const Process &other);
};

#endif
