#include <cassert>
#include "window.hpp"
#include "../errors.hpp"

LRESULT CALLBACK Window::GlobalWinProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    // Get pointer to base window object
    Window *wnd = nullptr;
    if (msg == WM_NCCREATE) {
        // Get pointer to Window from LPARAM (passed via CreateWindowEx)
        CREATESTRUCT *cs = (CREATESTRUCT *)lparam;
        wnd = (Window *)cs->lpCreateParams;

        // Explicitly set window object's m_hwnd:
        // While the message is processed, CreateWindowEx() has not yet finished,
        // and window object's m_hwnd is not yet set, but may be required by its WinProc.
        wnd->m_hwnd = hwnd;

        // Save pointer to Window in window's LongPtr
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)wnd);
    } else {
        wnd = (Window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    // Run window object's WinProc, if succeeded, or default one if failed
    if (wnd) {
        return wnd->WinProc(msg, wparam, lparam);
    } else {
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
}

Window::Window(const HINSTANCE &hInstance, const char *name) :
    m_hInstance(hInstance),
    m_name(name),
    m_hwnd(NULL),
    m_hdc(NULL),
    m_hglrc(NULL)
{
}

Window::~Window()
{
}

void Window::RegClass()
{
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_OWNDC;
    wc.hInstance = m_hInstance;
    wc.lpszClassName = ClassName();
    wc.lpfnWndProc = GlobalWinProc;
    if (!RegisterClassEx(&wc)) {
        throw WindowsError(ERR_CREATE_WINDOW_CLASS);
    }
}

void Window::Create()
{
    // Register window class, if not yet registered
    WNDCLASSEX wc = {0};
    if (!GetClassInfoEx(m_hInstance, ClassName(), &wc)) {
        RegClass();
    }

    // Create window
    m_hwnd = CreateWindowEx(
        0, ClassName(), m_name.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL,
        m_hInstance,
        this
    );
    if (m_hwnd == NULL) {
        throw Error(ERR_CREATE_WINDOW);
    }

    // Save window's device context
    m_hdc = GetDC(m_hwnd);
}

void Window::SetSimplePixelFormat()
{
    assert(m_hdc);

    // Select a simple pixel format: RGBA, 24-depth, 8-stencil
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;   //Flags
    pfd.iPixelType = PFD_TYPE_RGBA;     // The kind of framebuffer. RGBA or palette.
    pfd.cDepthBits = 24;                // bits for depth buffer
    pfd.cStencilBits = 8;               // bits for stencil buffer
    pfd.cAuxBuffers = 0;                // number of Aux buffers in the framebuffer
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
    if (pixelFormat == 0) {
        throw WindowsError(ERR_PIXEL_FORMAT);
    }

    // Set the pixel format, if found
    if (!SetPixelFormat(m_hdc, pixelFormat, &pfd)) {
        throw WindowsError(ERR_PIXEL_FORMAT);
    }
}

void Window::CreateOpenGLContext()
{
    assert(m_hdc);
    m_hglrc = wglCreateContext(m_hdc);
    if (!wglMakeCurrent(m_hdc, m_hglrc)) {
        throw WindowsError(ERR_OPENGL_CONTEXT);
    }
}

void Window::Destroy()
{
    if (m_hglrc) {
        assert(m_hdc);
        wglMakeCurrent(m_hdc, NULL);
        wglDeleteContext(m_hglrc);
        m_hglrc = NULL;
    }
    assert(m_hwnd);
    DestroyWindow(m_hwnd);
    m_hdc = NULL;
    m_hwnd = NULL;
}

// Window procedure for this Window class. For base Window, use the default WinProc.
LRESULT Window::WinProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    return DefWindowProc(m_hwnd, msg, wparam, lparam);
}

void Window::Show()
{
    ShowWindow(m_hwnd, SW_SHOWNORMAL);
}

long Window::PixelWidth() const
{
    RECT rect;
    GetWindowRect(m_hwnd, &rect);
    return (rect.right - rect.left);
}

long Window::PixelHeight() const
{
    RECT rect;
    GetWindowRect(m_hwnd, &rect);
    return (rect.bottom - rect.top);
}
