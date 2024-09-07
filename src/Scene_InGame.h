#pragma once
#include "Scene.h"

class Scene_InGame:  public Scene
{
protected:
    std::shared_ptr<Entity> player;
    std::string levelPath;
    bool drawTextures = true;
    bool drawGrid = false;
    bool drawBoundingBox =false;
    const Vec2 gridSize = Vec2 {64,64};
    sf::Text griTtext ;

    //void init();
    void loadLevel(const std::string & filename);


public:
    Scene_InGame(GameEngine * game_engine = nullptr);
    
    void sRender();

};