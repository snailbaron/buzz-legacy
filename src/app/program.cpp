#include "program.hpp"
#include "../gl_funcs.hpp"
#include "../errors.hpp"

Program::Program() :
    m_name(0),
    m_shaders(),
    m_linkStatus(0),
    m_linkLog()
{
    m_name = glCreateProgram();
    if (m_name == 0) {
        throw OpenGLError();
    }
}

Program::~Program()
{
    glDeleteProgram(m_name);
}

void Program::AttachShader(Shader &shader)
{
    m_shaders.push_back(shader);
    glAttachShader(m_name, shader.Name());
}

void Program::LoadShader(GLenum type, const char *fname)
{
    Shader shader(type, fname);
    shader.Compile();
    AttachShader(shader);
}

void Program::Link()
{
    glLinkProgram(m_name);
    glGetProgramiv(m_name, GL_LINK_STATUS, &m_linkStatus);

    GLint bufSize;
    glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &bufSize);
    GLchar *linkLog = new GLchar[bufSize];
    GLint logLen;
    glGetProgramInfoLog(m_name, bufSize, &logLen, linkLog);
    m_linkLog = std::string(linkLog);
    delete[] linkLog;
}

void Program::Use()
{
    glUseProgram(m_name);
}

const char * Program::LinkStatusString() const
{
    if (LinkSuccess()) {
        return "OK";
    } else {
        return "FAIL";
    }
}