#include "application.hpp"
#include "timer.hpp"
#include "window.hpp"
#include "../errors.hpp"
#include "../gl_funcs.hpp"
#include "../view/message_box.hpp"
#include <fstream>
#include <string>

// Define OpenGL extension functions here
#define FUNCTION(TYPE, NAME) TYPE NAME;
#include "gl_funcs_helper.inc"
#undef FUNCTION


Application g_app;

Application::Application(HINSTANCE hInstance) :
    m_hInstance(hInstance),
    m_game(),
    m_view(new HumanGameView()),
    m_program(nullptr)
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
    // Load OpenGL extension functions using a dummy OpenGL context
    Window dummyWindow(m_hInstance, "Dummy Window");
    dummyWindow.Create();
    dummyWindow.SetSimplePixelFormat();
    dummyWindow.CreateOpenGLContext();
    LoadOpenGLFunctions();
    dummyWindow.Destroy();
}

std::shared_ptr<OglWindow> Application::CreateOglWindow()
{
    std::shared_ptr<OglWindow> wnd(new OglWindow(m_hInstance, "OpenGL Window"));
    wnd->Create();
    wnd->SetFullPixelFormat();
    wnd->CreateFullOpenGLContext();
    wnd->Show();
    return wnd;
}

void Application::Init()
{
    // Initialize OpenGL graphics
    InitializeGfx();

    // Create view, with OpenGL context for rendering
    m_view = std::shared_ptr<HumanGameView>(new HumanGameView());
    m_view->Init();

    // Build OpenGL program
    BuildProgram();

    // Attach screen elements for rendering
    m_view->AttachScreenElement(std::shared_ptr<IScreenElement>(new MsgBox("Test message")));
    m_game.AddView(m_view);
}

void Application::Start()
{
    Timer timer;
    bool done = false;
    while (!done) {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                done = true;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        TimeMs deltaMs = timer.Reset();
        m_game.Update(deltaMs);
    }
}

void Application::Destroy()
{
}

void Application::BuildProgram()
{
    m_program = std::shared_ptr<Program>(new Program());
    m_program->LoadShader(GL_VERTEX_SHADER, "test.vert");
    m_program->LoadShader(GL_FRAGMENT_SHADER, "test.frag");
    m_program->Link();
    m_program->Use();
}