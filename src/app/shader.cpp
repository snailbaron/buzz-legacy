#include <fstream>
#include "shader.hpp"
#include "../errors.hpp"
#include "../gl_funcs.hpp"

Shader::Shader(GLenum type) :
    m_name(0),
    m_type(type),
    m_sourceFile(),
    m_source(),
    m_compileStatus(0),
    m_compileLog()
{
    m_name = glCreateShader(m_type);
    if (m_name == 0) {
        throw OpenGLError();
    }
}

Shader::Shader(GLenum type, const char *fname) :
    m_name(0),
    m_type(type),
    m_sourceFile(),
    m_source(),
    m_compileStatus(0),
    m_compileLog()
{
    m_name = glCreateShader(m_type);
    if (m_name == 0) {
        throw OpenGLError();
    }
    LoadSource(fname);
}

Shader::Shader(const Shader &other) :
    m_name(other.m_name),
    m_type(other.m_type),
    m_sourceFile(other.m_sourceFile),
    m_source(other.m_source),
    m_compileStatus(other.m_compileStatus),
    m_compileLog(other.m_compileLog)
{
}

Shader::~Shader()
{
}

Shader & Shader::operator=(const Shader &other)
{
    if (this != &other) {
        m_name = other.m_name;
        m_type = other.m_type;
        m_sourceFile = other.m_sourceFile;
        m_source = other.m_source;
        m_compileStatus = other.m_compileStatus;
        m_compileLog = other.m_compileLog;
    }
    return *this;
}

void Shader::LoadSource(const char *fname)
{
    m_sourceFile = std::string(fname);
    std::ifstream stream(fname);
    m_source = std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
    const GLchar *ptext = m_source.c_str();
    GLint len = (GLint)m_source.length();
    glShaderSource(m_name, 1, &ptext, &len);
}

void Shader::Compile()
{
    glCompileShader(m_name);
    glGetShaderiv(m_name, GL_COMPILE_STATUS, &m_compileStatus);

    GLint logBufSize;
    glGetShaderiv(m_name, GL_INFO_LOG_LENGTH, &logBufSize);
    GLchar *logBuffer = new GLchar[logBufSize];
    GLint logLen;
    glGetShaderInfoLog(m_name, logBufSize, &logLen, logBuffer);
    m_compileLog = std::string(logBuffer);
    delete[] logBuffer;
}

const char * Shader::TypeName() const
{
    switch (m_type) {
        case GL_VERTEX_SHADER:   return "GL_VERTEX_SHADER";
        case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
        default:                 return "UNKNOWN";
    }
}

const char * Shader::CompileStatusString() const
{
    if (CompileSuccess()) {
        return "OK";
    } else { 
        return "FAIL";
    }
}