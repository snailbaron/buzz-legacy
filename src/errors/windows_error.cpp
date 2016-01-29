#include "windows_error.hpp"

WindowsError::WindowsError(const ErrorCode &errCode) :
    Error(errCode),
    m_windowsErrCode(GetLastError())
{
}

WindowsError::~WindowsError()
{
}

const char * WindowsError::WindowsErrMessage() const
{
    static CHAR buffer[5000];
    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM,
        NULL,
        m_windowsErrCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        buffer,
        5000,
        NULL
    );
    return buffer;
}