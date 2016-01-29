#ifndef _WINDOWS_ERROR_HPP_
#define _WINDOWS_ERROR_HPP_

#include <Windows.h>
#include "error.hpp"

class WindowsError : public Error
{
public:
    WindowsError(const ErrorCode &errCode);
    virtual ~WindowsError();

    const DWORD WindowsErrCode() const { return m_windowsErrCode; }
    const char * WindowsErrMessage() const;

private:
    DWORD m_windowsErrCode;
};

#endif
