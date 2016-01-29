#ifndef _HUMAN_GAME_VIEW_HPP_
#define _HUMAN_GAME_VIEW_HPP_

#include <Windows.h>
#include <gl/GL.h>
#include <list>
#include <memory>
#include "game_view.hpp"
#include "../process_manager.hpp"
#include "screen_element.hpp"
#include "../app/ogl_window.hpp"

class HumanGameView : public IGameView
{
public:
    HumanGameView();
    ~HumanGameView();

    void Init();

    void AttachScreenElement(std::shared_ptr<IScreenElement> el);

    void Update(long deltaMs);
    void Render(long deltaMs);

    void SwapBuffers();

    // TODO: void LoseDevice();
    // TODO: void Restore();

    // TODO: Game view type & ID?

protected:
    ProcessManager m_processManager;
    std::list<std::shared_ptr<IScreenElement>> m_screenElements;
    std::shared_ptr<OglWindow> m_wnd;
    GLuint m_vao;

    // TODO: Mouse & keyboard handlers
};

#endif
