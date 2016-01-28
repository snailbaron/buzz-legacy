#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <Windows.h>

// Time in milliseconds. May represent time period or difference.
typedef long TimeMs;

class Timer
{
public:
    Timer();
    ~Timer();

    // Get current time on the timer.
    // The timer continues running, measuring time from the same baseine as before.
    TimeMs Check();

    // Get current time, and start measuring from now
    TimeMs Reset();

private:
    LARGE_INTEGER m_freq;
    LARGE_INTEGER m_baseline;
};

#endif
