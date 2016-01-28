#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <Windows.h>
#include <vector>

class Window
{
public:
    Window(const HINSTANCE &hInstance, const CHAR *name);
    virtual ~Window();

    const HWND Hwnd() const { return m_hwnd; }

    virtual void Init();
    virtual void Destroy();

protected:
    virtual LRESULT WinProc(UINT msg, WPARAM wparam, LPARAM lparam);

private:
    static const CHAR CLASS_NAME[];
    static LRESULT CALLBACK GlobalWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

    HINSTANCE m_hInstance;
    CHAR *m_name;
    HWND m_hwnd;
};

#endif
