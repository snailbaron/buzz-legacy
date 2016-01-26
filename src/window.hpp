#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <Windows.h>
#include <vector>

class Window
{
public:
    Window(const HINSTANCE &hInstance, const CHAR *name);
    virtual ~Window();

    void Init();
    void Destroy();
    const HWND Hwnd() const { return m_hwnd; }

protected:
    virtual LRESULT WinProc(UINT msg, WPARAM wparam, LPARAM lparam);

    virtual const CHAR * ClassName() const = 0;
    virtual const UINT ClassStyle() const { return 0; }
    virtual const DWORD WindowStyle() const { return 0; }

private:
    static LRESULT CALLBACK GlobalWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    HINSTANCE m_hInstance;
    HWND m_hwnd;
};

#endif
