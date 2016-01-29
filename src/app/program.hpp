#ifndef _PROGRAM_HPP_
#define _PROGRAM_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include <vector>
#include <string>
#include "shader.hpp"

class Program
{
public:
    Program();
    ~Program();

    const GLint Name() const { return m_name; }
    const std::vector<Shader> & Shaders() const { return m_shaders; }
    bool LinkSuccess() const { return (m_linkStatus == GL_TRUE); }
    const char * LinkStatusString() const;
    const std::string & LinkLog() const { return m_linkLog; }

    void AttachShader(Shader &shader);
    void LoadShader(GLenum type, const char *fname);
    void Link();
    void Use();

private:
    GLint m_name;
    std::vector<Shader> m_shaders;
    GLint m_linkStatus;
    std::string m_linkLog;
};

#endif
