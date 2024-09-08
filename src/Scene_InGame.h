#pragma once
#include "Scene.h"

class Scene_InGame:  public Scene
{
    struct PlayerConfig
    {
        float X,Y,CX,CY,SPEED,MAXSPEED,JUMP,GRAVITY;
        std::string WEAPON;
    };
    

protected:
    std::shared_ptr<Entity> player;
    std::string levelPath;
    PlayerConfig plConfig;
    bool drawTextures = true;
    bool drawGrid = false;
    bool drawBoundingBox =false;
    const Vec2 gridSize = Vec2 {64,64};
    sf::Text griTtext ;

    void init();

    void loadLevel(const std::string & filename);
    void update();
    void sDoAction(const Action &action);

    void onEnd();

public:
    Scene_InGame(const std::string & levelPathVar,GameEngine * game_engine = nullptr) ;
    
    void sRender();

};