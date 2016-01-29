#include "application.hpp"
#include "timer.hpp"
#include "window.hpp"
#include "../errors.hpp"
#include "../gl_funcs.hpp"
#include <fstream>
#include <string>

// Define OpenGL extension functions here
#define FUNCTION(TYPE, NAME) TYPE NAME;
#include "gl_funcs_helper.inc"
#undef FUNCTION


Application::Application(HINSTANCE hInstance) :
    m_hInstance(hInstance),
    m_wnd(hInstance, "Main"),
    m_oglDc(NULL),
    m_hglrc(NULL),
    m_game(),
    m_view(new HumanGameView())
{
}

Application::~Application()
{
}

void Application::LoadOpenGLFunctions()
{
#define FUNCTION(TYPE, NAME) NAME = (TYPE)wglGetProcAddress(#NAME);
#include "gl_funcs_helper.inc"
#undef FUNCTION
}

void Application::InitializeGfx()
{
     /* Create dummy OpenGL context */

    // Create dummy window, and get device context from it
    Window dummyWindow(m_hInstance, "Dummy Window");
    dummyWindow.Init();
    HDC dummyDc = GetDC(dummyWindow.Hwnd());

    // Set pixel format to a simple RGBA, 24-depth, 8-stencil
    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;   //Flags
    pfd.iPixelType = PFD_TYPE_RGBA;     // The kind of framebuffer. RGBA or palette.
    pfd.cDepthBits = 24;                // bits for depth buffer
    pfd.cStencilBits = 8;               // bits for stencil buffer
    pfd.cAuxBuffers = 0;                // number of Aux buffers in the framebuffer
    pfd.iLayerType = PFD_MAIN_PLANE;
    int pixelFormat = ChoosePixelFormat(dummyDc, &pfd);
    if (pixelFormat == 0) {
        throw Error(ERR_PIXEL_FORMAT);
    }
    if (!SetPixelFormat(dummyDc, pixelFormat, &pfd)) {
        throw Error(ERR_PIXEL_FORMAT);
    }

    // Create and activate a dummy OpenGL context
    HGLRC dummyContext = wglCreateContext(dummyDc);
    if (!wglMakeCurrent(dummyDc, dummyContext)) {
        throw Error(ERR_OPENGL_CONTEXT);
    }

    // Load OpenGL & WGL extension functions
    LoadOpenGLFunctions();

    // Destroy dummy OpenGL context and window
    wglMakeCurrent(dummyDc, NULL);
    wglDeleteContext(dummyContext);
    dummyWindow.Destroy();


    /* Create proper OpenGL context */

    // Create window and get its device context
    m_wnd.Init();
    m_oglDc = GetDC(m_wnd.Hwnd());

    // Set pixel format
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
    if (!wglChoosePixelFormatARB(m_oglDc, attrs, NULL, 1, &pixelFormat, &numFormats)) {
        throw Error(ERR_PIXEL_FORMAT);
    }
    if (!SetPixelFormat(m_oglDc, pixelFormat, &pfd)) {
        throw WindowsError(ERR_PIXEL_FORMAT);
    }

    // Create OpenGL context
    const int contextAttrs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 0,
        0
    };
    m_hglrc = wglCreateContextAttribsARB(m_oglDc, 0, contextAttrs);
    if (!wglMakeCurrent(m_oglDc, m_hglrc)) {
        throw WindowsError(ERR_OPENGL_CONTEXT);
    }

    // Show main window
    ShowWindow(m_wnd.Hwnd(), SW_SHOWNORMAL);
}

void Application::Init()
{
    // Initialize OpenGL graphics
    InitializeGfx();
}

void Application::Start()
{
    m_game.AddView(m_view);

    Timer timer;
    bool done = false;
    while (!done) {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        TimeMs deltaMs = timer.Reset();
        m_game.Update(deltaMs);
    }
}

void Application::Destroy()
{
    // Delete OpenGL context
    wglMakeCurrent(m_oglDc, NULL);
    wglDeleteContext(m_hglrc);
    m_wnd.Destroy();
}

