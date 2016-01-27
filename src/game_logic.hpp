#ifndef _GAME_LOGIC_HPP_
#define _GAME_LOGIC_HPP_

#include <memory>
#include <string>

typedef unsigned int ActorId;

class GameLogic
{
public:
    virtual std::shared_ptr<Actor> GetActor(const ActorId id) = 0;
    virtual void AddActor(std::shared_ptr<Actor> actor, ActorParams *p) = 0;
    virtual void MoveActor(const ActorId &id, const Mat4x4 &mat) = 0;
    virtual void RemoveActor(ActorId id) = 0;
    virtual bool LoadGame(std::string gameName) = 0;
    virtual void OnUpdate(float time, float elapsedTime) = 0;
    virtual void ChangeState(BaseGameState newState) = 0;
};

#endif
