#pragma once
#include "Scene.h"

class Scene_Menu: public Scene
{
public:
    void init();
    void sRender();
    void update();
    void sDoAction(const Action & action);
    void onEnd();
    void doAction(const Action& Action);


    Scene_Menu(GameEngine * game_engine = nullptr);
};
