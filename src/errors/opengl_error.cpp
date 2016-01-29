#include "opengl_error.hpp"

OpenGLError::OpenGLError(const ErrorCode &errCode) :
    Error(errCode),
    m_oglErrCode(glGetError())
{
}

OpenGLError::~OpenGLError()
{
}

const char * OpenGLError::OglErrName() const
{
    switch (m_oglErrCode) {
        case GL_INVALID_ENUM:      return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:     return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_OUT_OF_MEMORY:     return "GL_OUT_OF_MEMORY";
        case GL_STACK_OVERFLOW:    return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:   return "GL_STACK_UNDERFLOW";
        default:                   return "UNKNOWN";
    }
}