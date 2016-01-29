#include "human_game_view.hpp"
#include "../app/window.hpp"
#include "../gl_funcs.hpp"
#include "../app/application.hpp"

HumanGameView::HumanGameView() :
    m_processManager(),
    m_screenElements(),
    m_wnd(nullptr)
{
}

HumanGameView::~HumanGameView()
{
}

void HumanGameView::Init()
{
    m_wnd = g_app.CreateOglWindow();
    long w = m_wnd->PixelWidth();
    long h = m_wnd->PixelHeight();
    GLfloat xscale, yscale;
    if (w >= h) {
        yscale = 1.0f;
        xscale = 1.0f * h / w;
    } else {
        xscale = 1.0f;
        yscale = 1.0f * w / h;
    }

    GLint guiMatrixLoc = glGetUniformLocation(g_app.GetProgram()->Name(), "guiMatrix");
    GLfloat guiMatrixData[] = {
        xscale * 2.0f, 0.0f, -1.0f,
        0.0f, yscale * 2.0f, -1.0f,
        0.0f, 0.0f, 1.0f,
    };
    glUniformMatrix3fv(guiMatrixLoc, 1, GL_TRUE, guiMatrixData);

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
}

void HumanGameView::Update(long deltaMs)
{
    // Update running view-side processes
    m_processManager.UpdateProcesses(deltaMs);

    // Update screen elements
    for (auto i = m_screenElements.begin(); i != m_screenElements.end(); i++) {
        (*i)->Update(deltaMs);
    }
}

void HumanGameView::Render(long deltaMs)
{
    // TODO: Check refresh rate? Render only if it's time to. May involve remembering last draw time/tick.

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto i = m_screenElements.begin(); i != m_screenElements.end(); i++) {
        (*i)->Render(deltaMs);
    }
    glFinish();
    SwapBuffers();    
}

void HumanGameView::AttachScreenElement(std::shared_ptr<IScreenElement> el)
{
    m_screenElements.push_back(el);
}

void HumanGameView::SwapBuffers()
{
    ::SwapBuffers(m_wnd->Hdc());
}