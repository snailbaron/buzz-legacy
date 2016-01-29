#ifndef _OGL_WINDOW_HPP_
#define _OGL_WINDOW_HPP_

#include "window.hpp"

class OglWindow : public Window
{
public:
    OglWindow(const HINSTANCE &hInstance, const char *name);
    virtual ~OglWindow();

    void SetFullPixelFormat();
    void CreateFullOpenGLContext();

protected:
    virtual const char * ClassName() const { return "OglWindowClass"; }
    virtual LRESULT WinProc(UINT msg, WPARAM wparam, LPARAM lparam);
};

#endif
