#include <iostream>
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
    std::cerr << "Created program: " << m_name << std::endl;
}

Program::~Program()
{
    glDeleteProgram(m_name);
    std::cerr << "Deleted program: " << m_name << std::endl;
}

void Program::AttachShader(Shader &shader)
{
    std::cerr << "Program " << m_name << ": attaching shader " << shader.Name() << " (" << shader.TypeName() << ")" << std::endl;
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
    std::cerr << "Linking program " << m_name << std::endl;
    glLinkProgram(m_name);
    glGetProgramiv(m_name, GL_LINK_STATUS, &m_linkStatus);
    std::cerr << "Link status: " << (m_linkStatus ? "OK" : "FAIL") << std::endl;

    GLint bufSize;
    glGetProgramiv(m_name, GL_INFO_LOG_LENGTH, &bufSize);
    GLchar *linkLog = new GLchar[bufSize];
    GLint logLen;
    glGetProgramInfoLog(m_name, bufSize, &logLen, linkLog);
    m_linkLog = std::string(linkLog);
    delete[] linkLog;
    std::cerr << "Link log:" << std::endl << m_linkLog << std::endl;
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