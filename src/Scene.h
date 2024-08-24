#pragma once
#include "EntityManager.h"
#include "Action.h"

class Scene
{
private:
    GameEngine g;
    EntityManager entities;
    int current_frame;
    std::map<int,std::string> actionMap;
    bool paused;
    bool hasEnded;

public:
    virtual void update() = 0;
    virtual void sDoAction(Action action) = 0;
    virtual void sRender() = 0;

    void simulate(int i);
    void doAction(Action action);
    void registerAction(Action action);
};