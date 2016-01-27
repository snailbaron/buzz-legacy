#include "main_window.hpp"
#include "gl_funcs_def.hpp"
#include "error.hpp"

void MainWindow::Init()
{
    // Initialize base window
    Window::Init();

    // Get window's device context
    m_dc = GetDC(Hwnd());

    // Choose pixel format with WGL extension
    const int attrs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };
    int pixelFormat;
    UINT numFormats;
    if (!wglChoosePixelFormatARB(m_dc, attrs, NULL, 1, &pixelFormat, &numFormats)) {
        throw Error(ERR_PIXEL_FORMAT);
    }

    HGLRC context = wglCreateContextAttribsARB(m_dc, 0, attrs);
    wglMakeCurrent(m_dc, context);
}

void MainWindow::Destroy()
{
    // Delete OpenGL context
    wglMakeCurrent(m_dc, NULL);
    wglDeleteContext(m_context);

    // Destroy base window
    Window::Destroy();
}

LRESULT MainWindow::WinProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    // If nothing matched, fall back to base window's WinProc
    return Window::WinProc(msg, wparam, lparam);
}