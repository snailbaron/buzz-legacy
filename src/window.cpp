#include <strsafe.h>
#include "window.hpp"
#include "error.hpp"

LRESULT CALLBACK Window::GlobalWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    // Get pointer to base window object
    Window *wnd = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT *cs = (CREATESTRUCT *)lparam;
        wnd = (Window *)cs->lpCreateParams;

        // Explicitly set window object's m_hwnd:
        // While the message is processed, CreateWindowEx() has not yet finished,
        // and window object's m_hwnd is not yet set, but may be required by its WinProc.
        wnd->m_hwnd = hwnd;
    } else {
        wnd = (Window *)GetWindowLongPtr(hwnd, 0);
    }

    // Run window object's WinProc, if succeeded, or default one if failed
    if (wnd) {
        return wnd->WinProc(msg, wparam, lparam);
    } else {
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}

Window::Window(const HINSTANCE &hInstance, const CHAR *name) :
    m_hInstance(hInstance), m_hwnd(NULL)
{
    // Register window class, if not yet registered
    WNDCLASSEX wc = {0};
    if (!GetClassInfoEx(m_hInstance, ClassName(), &wc)) {
         /* Create dummy window with dummy OpenGL context */
        WNDCLASSEX wc = {0};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = ClassStyle();
        wc.hInstance = m_hInstance;
        wc.lpszClassName = ClassName();
        wc.lpfnWndProc = GlobalWinProc;
        if (!RegisterClassEx(&wc)) {
            throw Error(ERR_CREATE_WINDOW_CLASS);
        }
    }

    // Create window
    m_hwnd = CreateWindowEx(
        0, ClassName(), name,
        WindowStyle(),
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL,
        m_hInstance,
        this
    );
    if (m_hwnd == NULL) {
        throw Error(ERR_CREATE_WINDOW);
    }
}

Window::~Window()
{
    // Destroy underlying window
    DestroyWindow(m_hwnd);
}

// Window procedure for this Window class. For base Window, use the default WinProc.
LRESULT Window::WinProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    return DefWindowProc(m_hwnd, msg, wparam, lparam);
}

