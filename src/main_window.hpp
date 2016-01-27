#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include "window.hpp"

class MainWindow : public Window
{
public:
    MainWindow(HINSTANCE hInstance) :
        Window(hInstance, "Main"), m_dc(NULL), m_context(NULL) {}
    virtual ~MainWindow() {}

    virtual void Init();
    virtual void Destroy();

protected:
    virtual LRESULT WinProc(UINT msg, WPARAM wparam, LPARAM lparam);

    virtual const CHAR * ClassName() const { return "MainWindowClass"; }
    virtual const UINT ClassStyle() const { return CS_OWNDC; }
    virtual const DWORD WindowStyle() const { return WS_OVERLAPPEDWINDOW | WS_VISIBLE; }

    HDC m_dc;
    HGLRC m_context;
};

#endif
