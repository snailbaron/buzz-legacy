#ifndef _MESSAGE_BOX_HPP_
#define _MESSAGE_BOX_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include <string>
#include "screen_element.hpp"

class MsgBox : public IScreenElement
{
public:
    MsgBox(const std::string &msg);
    virtual ~MsgBox();

    virtual void Render(long deltaMs);
    virtual void Update(long deltaMs);

protected:
    std::string m_msg;
    float m_x, m_y;
    float m_w, m_h;
    GLuint m_bufName;
};

#endif
