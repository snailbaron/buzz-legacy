#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <list>
#include <memory>
#include "../process_manager.hpp"
#include "../game_view.hpp"

enum class GameState
{
    Starting,
    Running,
};

/**
 * Core game logic class.
 *
 * The class manages:
 *   * Game views, attached to human or AI players
 *   * Game states
 *   * Processes for game logic
 *
 * Additional ideas:
 *   * RNG
 *   * Direct Actor management (Actor map/list in game logic)
 *   * Something about players (their number at least)
*/
class Game
{
public:
    Game();     // Maybe pass game options?
    ~Game();

    // Working with game views
    void AddView(std::shared_ptr<IGameView> view);

    // Working with game state
    void ChangeState(const GameState &state);

    // Regular update function
    void Update(long deltaMs);

private:
    GameState m_gameState;
    ProcessManager m_processManager;
    std::list<std::shared_ptr<IGameView>> m_gameViews;
};

#endif
