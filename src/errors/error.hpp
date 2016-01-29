#ifndef _ERROR_HPP_
#define _ERROR_HPP_

enum ErrorCode
{
    ERR_CREATE_WINDOW_CLASS,
    ERR_CREATE_WINDOW,
    ERR_PIXEL_FORMAT,
    ERR_OPENGL_CONTEXT,
    ERR_INIT_NOT_ENOUGH_DISK_SPACE,
    ERR_INIT_NOT_ENOUGH_PHYS_MEMORY,
    ERR_INIT_NOT_ENOUGH_VIRT_MEMORY,
    ERR_INIT_NOT_ENOUGH_CONTIG_MEMORY,
    ERR_OPENGL,
};

class Error
{
public:
    Error(const ErrorCode &errCode) : m_errCode(errCode) {}
    virtual ~Error() {}

    const ErrorCode & ErrCode() const { return m_errCode; }

private:
    ErrorCode m_errCode;
};

#endif
