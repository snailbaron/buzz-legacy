#include <cassert>
#include "base_game_logic.hpp"

void BaseGameLogic::OnUpdate(float time, float elapsedTime)
{
    int deltaMs = int(elapsedTime * 1000.f);
    switch (m_state) {
        case BaseGameState::Initializing:
            ChangeState(BaseGameState::LoadingGameEnvironment);
            break;

        case BaseGameState::LoadingGameEnvironment:
            if (g_app->LoadGame()) {
                ChangeState(BaseGameState::WaitingForPlayers);
            } else {
                assert(0 && "The game failed to load");
                g_app->AbortGame();
            }
            break;

        case BaseGameState::WaitingForPlayers:
            if (m_expectedPlayers == m_gameViews.size()) {
                ChangeState(BaseGameState::Running);
            }
            break;

        case BaseGameState::Running:
            m_processManager->UpdateProcesses(deltaMs);
            break;

        default:
            assert(0 && "Unrecognized state");
            // TODO: Throw exception?
    }

    for (GameViewList::iterator i = m_gameViews.begin(); i != m_gameViews.end(); i++) {
        (*i)->OnUpdate(deltaMs);
    }
}