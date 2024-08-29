#pragma once
#include "Scene.h"

class Scene_Menu: public Scene
{
public:
    void sRender();
    void update();
    void sDoAction(Action action);


    Scene_Menu(GameEngine * game_engine = nullptr);
};
