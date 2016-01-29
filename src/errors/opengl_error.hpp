#ifndef _OPENGL_ERROR_HPP_
#define _OPENGL_ERROR_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include "error.hpp"

class OpenGLError : public Error
{
public:
    OpenGLError(const ErrorCode &errCode = ERR_OPENGL);
    virtual ~OpenGLError();

    const GLenum OglErrCode() const { return m_oglErrCode; }
    const char * OglErrName() const;

private:
    GLenum m_oglErrCode;
};

#endif
