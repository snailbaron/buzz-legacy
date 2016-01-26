#include "dummy_ogl_window.hpp"
#include "error.hpp"

DummyOglWindow::DummyOglWindow(const HINSTANCE &hInstance) :
    Window(hInstance, "DummyOglWindow")
{
    // Get device context for this window
    m_dc = GetDC(Hwnd());

    // Choose pixel format. Use simple RGBA, 24-depth, 8-stencil framebuffer.
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;   //Flags
    pfd.iPixelType = PFD_TYPE_RGBA;     // The kind of framebuffer. RGBA or palette.
    pfd.cDepthBits = 24;                // bits for depth buffer
    pfd.cStencilBits = 8;               // bits for stencil buffer
    pfd.cAuxBuffers = 0;                // number of Aux buffers in the framebuffer
    pfd.iLayerType = PFD_MAIN_PLANE;
    int pixelFormat = ChoosePixelFormat(m_dc, &pfd);
    if (pixelFormat == 0) {
        throw Error(ERR_PIXEL_FORMAT);
    }

    // Set pixel format, if found
    if (!SetPixelFormat(m_dc, pixelFormat, &pfd)) {
        throw Error(ERR_PIXEL_FORMAT);
    }

    // Create and activate a dummy OpenGL context
    m_context = wglCreateContext(m_dc);
    if (!wglMakeCurrent(m_dc, m_context)) {
        throw Error(ERR_OPENGL_CONTEXT);
    }
}

DummyOglWindow::~DummyOglWindow()
{
    // Delete dummy OpenGL context
    wglMakeCurrent(m_dc, NULL);
    wglDeleteContext(m_context);
}

