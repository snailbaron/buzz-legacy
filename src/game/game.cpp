#include "game.hpp"

Game::Game() :
    m_gameState(GameState::Starting),
    m_processManager(),
    m_gameViews()
{
}

Game::~Game()
{
}

void Game::AddView(std::shared_ptr<IGameView> view)
{
    m_gameViews.push_back(view);
}

void Game::ChangeState(const GameState &state)
{
    // TODO: Some FSM-like behavior for changing states. When there are states.
}

void Game::Update(long deltaMs)
{
    // TODO: Update game world by deltaMS time

    // Update plan:
    // * Get state, process accordingly. A change state may be required.
    // * Update running processes
    // * Update underlying views
}