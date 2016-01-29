#include "../app/application.hpp"
#include "../gl_funcs.hpp"
#include "message_box.hpp"

MsgBox::MsgBox(const std::string &msg) :
    m_msg(msg),
    m_x(0.01f), m_y(0.01f),
    m_w(0.4f), m_h(0.4f)
{
    GLfloat data[] = {
        0.0f, 0.0f,
        0.0f, m_y,
        m_x, m_y,
        m_x, 0.0f
    };
    
    glGenBuffers(1, &m_bufName);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufName);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), data, GL_STATIC_DRAW);
}

MsgBox::~MsgBox()
{
    glDeleteBuffers(1, &m_bufName);
}

void MsgBox::Render(long deltaMs)
{
    GLint guiPosLoc = glGetUniformLocation(g_app.GetProgram()->Name(), "guiPos");
    glUniform2f(guiPosLoc, m_x, m_y);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_bufName);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(0);
}

void MsgBox::Update(long deltaMs)
{
}
