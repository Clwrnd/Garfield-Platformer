#pragma once

#include "EntityManager.h"
#include "Action.h"

class GameEngine;

typedef std::map<int, std::string> ActionMap;

class Scene
{

protected:

    GameEngine * g = nullptr;
    EntityManager entities;
    int current_frame;
    ActionMap actionMap;
    bool paused;
    bool hasEnded;

public:

    Scene();
    Scene(GameEngine * gameEngine);

    virtual void update() = 0;
    virtual void sDoAction(Action action) = 0;
    virtual void sRender() = 0;

    void simulate(int i);
    void doAction(Action action);
    void registerAction(Action action);
};