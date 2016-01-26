#ifndef _ERROR_HPP_
#define _ERROR_HPP_

enum ErrorCode
{
    ERR_CREATE_WINDOW_CLASS,
    ERR_CREATE_WINDOW,
    ERR_PIXEL_FORMAT,
    ERR_OPENGL_CONTEXT,
};

class Error
{
public:
    Error(const ErrorCode &errCode) : m_errCode(errCode) {}
    const ErrorCode & ErrCode() const { return m_errCode; }

private:
    ErrorCode m_errCode;
};

#endif
