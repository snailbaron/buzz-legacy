#include "human_view.hpp"

void HumanView::OnRender(double time, float elapsedTime)
{
    m_currTick = timeGetTime();
    if (m_currTick == m_lastDraw) {
        return;
    }

    HRESULT hr;

    if (m_runFullSpeed || m_currTick - m_lastDraw > SCREEN_REFRESH_RATE) {
        // TODO: Clear render target and Z-buffer

        // TODO: Render scene: iterate over SceneElements in list, call OnRender()

        m_lastDraw = m_currTick;
    }
}

HRESULT HumanView::OnRestore()
{
    HRESULT hr = S_OK;
    
    // TODO: Initialize fonts (+ create sprites), if required
    // TODO: Iterate over SceneElements, call OnRestore()

    return hr;
}

void HumanView::OnLostDevice()
{
    // TODO: Call OnLostDevice where applicable, safe-release some sprites, etc.
}

void HumanView::OnUpdate(int deltaMs)
{
    // Update running processes (like UI animations)
    m_processManager->UpdateProcesses(deltaMs);

    // Update screen elements
    for (ScreenElementList::iterator i = m_screenElements.begin(); i != m_screenElements.end(); i++) {
        (*it)->OnUpdate(deltaMs);
    }
}

