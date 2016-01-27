#ifndef _HUMAN_GAME_VIEW_HPP_
#define _HUMAN_GAME_VIEW_HPP_

#include <list>
#include <memory>
#include "game_view.hpp"
#include "process_manager.hpp"
#include "screen_element.hpp"

class HumanGameView : public IGameView
{
public:
    void Update(long deltaMs);
    void Render(long deltaMs);

    // TODO: void LoseDevice();
    // TODO: void Restore();

    // TODO: Game view type & ID?

protected:
    ProcessManager m_processManager;
    std::list<std::shared_ptr<IScreenElement>> m_screenElements;
    // TODO: Mouse & keyboard handlers
};

#endif
