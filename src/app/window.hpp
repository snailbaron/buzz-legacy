/*
 * Basic window class
 *
 * Device context is created for each window (CS_OWNDC is set).
 * Default window procedure is used.
 *
 * This window class may be used as-is (to get a dummy window), or
 * as a base class, to provide more functionality.
 *
 * Inheriting classes should overwrite:
 *   * ClassName() - to register a separate window class
 *   * WinProc() - to provide custom window procedure
 */

#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <Windows.h>
#include <string>

class Window
{
public:
    Window(const HINSTANCE &hInstance, const char *name);
    virtual ~Window();

    const HWND Hwnd() const { return m_hwnd; }
    const HDC Hdc() const { return m_hdc; }

    long PixelWidth() const;
    long PixelHeight() const;

    void Show();

    void RegClass();
    void Create();
    void SetSimplePixelFormat();
    void CreateOpenGLContext();

    void Destroy();

protected:
    virtual LRESULT WinProc(UINT msg, WPARAM wparam, LPARAM lparam);
    virtual const char * ClassName() const { return "WindowClass"; }

    HINSTANCE m_hInstance;
    std::string m_name;
    HWND m_hwnd;
    HDC m_hdc;
    HGLRC m_hglrc;

private:
    static LRESULT CALLBACK GlobalWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};

#endif
