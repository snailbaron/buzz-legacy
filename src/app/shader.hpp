#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include <string>

class Shader
{
public:
    Shader(GLenum type);
    Shader(GLenum type, const char *fname);
    Shader(const Shader &other);
    ~Shader();

    Shader & operator=(const Shader &other);

    GLuint Name() const { return m_name; }
    GLenum Type() const { return m_type; }
    const char * TypeName() const;
    const std::string & SourceFile() const { return m_sourceFile; }
    const std::string & Source() const { return m_source; }
    bool CompileSuccess() const { return (m_compileStatus == GL_TRUE); }
    const std::string & CompileLog() const { return m_compileLog; }

    void LoadSource(const char *fname);
    void Compile();

private:
    GLuint m_name;
    GLenum m_type;
    std::string m_sourceFile;
    std::string m_source;
    GLint m_compileStatus;
    std::string m_compileLog;
};

#endif
