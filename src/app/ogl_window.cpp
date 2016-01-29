#include "ogl_window.hpp"
#include "../gl_funcs.hpp"
#include "../errors.hpp"

OglWindow::OglWindow(const HINSTANCE &hInstance, const char *name) :
    Window(hInstance, name)
{
}

OglWindow::~OglWindow()
{
}

LRESULT OglWindow::WinProc(UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return Window::WinProc(msg, wparam, lparam);
}

void OglWindow::SetFullPixelFormat()
{
    // Select pixel format using WGL extension
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
    UINT numFormats;
    int pixelFormat;
    if (!wglChoosePixelFormatARB(m_hdc, attrs, NULL, 1, &pixelFormat, &numFormats)) {
        throw WindowsError(ERR_PIXEL_FORMAT);
    }

    // Set selected pixel format. PIXELFORMATDESCRIPTOR is ignored.
    PIXELFORMATDESCRIPTOR pfd;
    if (!SetPixelFormat(m_hdc, pixelFormat, &pfd)) {
        throw WindowsError(ERR_PIXEL_FORMAT);
    }
}

void OglWindow::CreateFullOpenGLContext()
{
    // Create OpenGL context
    const int contextAttrs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 0,
        0
    };
    m_hglrc = wglCreateContextAttribsARB(m_hdc, 0, contextAttrs);
    if (!wglMakeCurrent(m_hdc, m_hglrc)) {
        throw WindowsError(ERR_OPENGL_CONTEXT);
    }
}