/*
 * Dummy OpenGL window. Allows to create a dummy OpenGL context
 * to query the system, and load extension functions.
 */

#ifndef _DUMMY_OGL_WINDOW_HPP_
#define _DUMMY_OGL_WINDOW_HPP_

#include "window.hpp"

class DummyOglWindow : public Window
{
public:
    DummyOglWindow(const HINSTANCE &hInstance) :
        Window(hInstance, "DummyOglWindow"), m_dc(NULL), m_context(NULL) {}
    virtual ~DummyOglWindow() {}

    const HDC Dc() const { return m_dc; }
    const HGLRC Context() const { return m_context; }

    virtual void Init();
    virtual void Destroy();

protected:
    virtual const CHAR * ClassName() const { return "DummyOglWindowClass"; }
    virtual const UINT ClassStyle() const { return CS_OWNDC; }
    virtual const DWORD WindowStyle() const { return 0; }

    HDC m_dc;
    HGLRC m_context;
};


#endif
