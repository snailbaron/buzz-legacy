#ifndef _BASE_GAME_LOGIC_HPP_
#define _BASE_GAME_LOGIC_HPP_

#include <map>
#include "game_logic.hpp"
#include "process_manager.hpp"

typedef std::map<ActorId, std::shared_ptr<Actor>> ActorMap;

enum class BaseGameState
{
    Initializing,
    LoadingGameEnvironment,
    WaitingForPlayers,
    Running,
};

class BaseGameLogic : public GameLogic
{
    // friend class App?
    // To get access to view list

public:
    BaseGameLogic(const GameOptions &options);
    virtual ~BaseGameLogic();

    void TogglePause(bool active);
    void SetPlayer(GameViewType type, GameViewId viewId, ActorId actorId);

    virtual void AddView(std::shared_ptr<GameView> view);
    virtual void AddActor(std::shared_ptr<Actor> actor, ActorParams *p);
    virtual std::shared_ptr<Actor> GetActor(const ActorId id);
    virtual void RemoveActor(ActorId id);
    virtual void MoveActor(const ActorId id, const Mat4x4 &mat);
    virtual bool LoadGame(std::string gameName) { return true; }
    virtual void OnUpdate(float time, float elapsedTime);
    virtual void ChangeState(BaseGameState newState);
    virtual void RenderDiagnostics() {}

protected:
    ProcessManager *m_processManager;
    Random m_random;    // RNG
    GameViewList m_gameViews;       // view attached to the game

    ActorMap m_actorMap;
    ActorId m_lastActorId;

    BaseGameState m_state;
    int m_expectedPlayers;
};

#endif
