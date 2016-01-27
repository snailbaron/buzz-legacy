#ifndef _ERROR_HPP_
#define _ERROR_HPP_

enum ErrorCode {
    ERR_INIT_NOT_ENOUGH_DISK_SPACE,
    ERR_INIT_NOT_ENOUGH_PHYS_MEMORY,
    ERR_INIT_NOT_ENOUGH_VIRT_MEMORY,
    ERR_INIT_NOT_ENOUGH_CONTIG_MEMORY,
    ERR_INIT_CPU_TOO_SLOW,
};

class Error
{
public:
    Error(const ErrorCode errCode) : m_errCode(errCode) {}

    const ErrorCode Code() const { return m_errCode; }

private:
    ErrorCode m_errCode;

};


#endif
