#include "human_game_view.hpp"
#include "../app/window.hpp"

HumanGameView::HumanGameView() :
    m_processManager(),
    m_screenElements()
{
}

HumanGameView::~HumanGameView()
{
}

void HumanGameView::Init()
{
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

    // TODO: Clear render target and z-buffer

    for (auto i = m_screenElements.begin(); i != m_screenElements.end(); i++) {
        (*i)->Render(deltaMs);
    }
}
