#include "timer.hpp"

Timer::Timer()
{
    QueryPerformanceFrequency(&m_freq);
    QueryPerformanceCounter(&m_baseline);
}

Timer::~Timer()
{
}

TimeMs Timer::Check()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);

    double timeSec = (double)(ticks.QuadPart - m_baseline.QuadPart) / m_freq.QuadPart;
    return (TimeMs)(timeSec * 1000.0);
}

TimeMs Timer::Reset()
{
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);

    double timeSec = (double)(ticks.QuadPart - m_baseline.QuadPart) / m_freq.QuadPart;
    m_baseline = ticks;

    return (TimeMs)(timeSec * 1000.0);
}