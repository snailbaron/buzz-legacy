#ifndef _LOG_HPP_
#define _LOG_HPP_

#include <iostream>
#include <ostream>
#include <string>

enum class LogMode
{
    DEBUG,
    INFO,
    ERR,
};

class Log
{
public:
    Log() {}
    virtual ~Log() {}

    void SetMode(const LogMode &mode) { m_mode = mode; }

    template <class T> const Log & operator<<(const T &value) const {
        std::cerr << value;
        return *this;
    }

protected:
    LogMode m_mode;
};

Log g_log;

#endif
