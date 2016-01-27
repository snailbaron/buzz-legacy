#ifndef _HUMAN_VIEW_HPP_
#define _HUMAN_VIEW_HPP_

#include <Windows.h>
#include <list>
#include <memory>
#include "optional.hpp"
#include "process_manager.hpp"
#include "input_handlers.hpp"

typedef std::list<std::shared_ptr<ScreenElement>> ScreenElementList;

class HumanView : public GameView
{
public:
    HumanView();
    ~HumanView();

    ScreenElementList screenElements;

    // GameView interface
    virtual HRESULT OnRestore();
    virtual void OnRender(double time, float elapsedTime);
    virtual void OnLostDevice();
    virtual GameViewType GetType() { return GameViewType::Human; }
    virtual GameViewId GetId() const { return m_viewId; }

    virtual void OnAttach(GameViewId viewId, Opt<ActorId> actorId) { m_viewId = viewId; m_actorId = actorId; }
    virtual LRESULT CALLBACK OnMsgProc(AppMsg msg);
    virtual void OnUpdate(int deltaMs);

    // Layering of iterface elements
    virtual void PushElement(std::shared_ptr<ScreenElement> screen);
    virtual void PopElement();

    std::shared_ptr<MouseHandler> m_mouseHandler;
    std::shared_ptr<KeyboardHandler> m_keyboardHandler;

    // TODO: Audio: bool InitAudio(); 

protected:
    GameViewId m_viewId;
    Opt<ActorId> m_actorId;
    ProcessManager *m_processManager;

    DWORD m_currTick;
    DWORD m_lastDraw;
    bool m_runFullSpeed;

    // Font, sprite, render text

};

#endif
