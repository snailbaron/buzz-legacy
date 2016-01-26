#pragma once

#include "window.hpp"

class GameWindow : public Window
{
public:
    GameWindow(const HINSTANCE &hInstance, const CHAR *name) :
        Window(hInstance, name) {}
    virtual ~GameWindow() {}

protected:
    virtual const CHAR * ClassName() const { return "GameWindowClass"; }
    virtual const UINT ClassStyle() const { return CS_OWNDC; }
    virtual const DWORD WindowStyle() const { return WS_OVERLAPPEDWINDOW | WS_VISIBLE; }

    virtual LRESULT WinProc(UINT msg, WPARAM wparam, LPARAM lparam);
};