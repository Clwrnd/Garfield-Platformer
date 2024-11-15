#pragma once

#include "EntityManager.h"
#include "Action.h"

class GameEngine;

typedef std::map<int, std::string> ActionMap;

class Scene
{
protected:
    GameEngine *game_engine = nullptr;
    EntityManager entities;
    ActionMap actionMap;
    size_t current_frame = 0;
    bool paused = false;
    bool hasEnded = false;
    const bool isAreplay = false;

    virtual void onEnd() = 0;
    void setPaused(bool paused);

public:
    Scene();
    Scene(GameEngine *g);
    Scene(GameEngine *g, bool isAr);
    ~Scene();

    virtual void update() = 0;
    virtual void sDoAction(const Action &action) = 0;
    virtual void sRender() = 0;

    virtual void doAction(const Action &action);
    void simulate(const size_t i);
    void registerAction(int inputKey, const std::string &actionName);

    size_t width() const;
    size_t height() const;
    size_t getCurrentFrame() const;

    bool getHasEnded() const;
    const ActionMap &getActionMap() const;
    void drawLine(const Vec2 &p1, const Vec2 &p2);

    const bool isAReplay() const;
};