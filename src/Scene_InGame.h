#pragma once
#include "Scene.h"
#include <SFML/Audio.hpp>

#include <iostream>
#include <fstream>

class Scene_InGame : public Scene
{
    struct PlayerConfig
    {
        float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY, BULLETS, BULLETL, BULLETA;
        std::string WEAPON;
    };

protected:
    std::shared_ptr<Entity> player;
    std::ofstream replayFile;
    std::string levelPath;
    PlayerConfig plConfig;
    bool drawTextures = true;
    bool drawGrid = false;
    bool drawBoundingBox = false;
    bool paused = false;
    bool isAreplay = false;
    const Vec2 gridSize = Vec2{64, 64};
    sf::Text griTtext;
    sf::Text timeString;
    sf::Text coinCout;
    sf::Sound soundEffects;
    std::clock_t time_ref;
    unsigned char coin_count = 0;

    void init();

    void loadLevel(const std::string &filename);
    void update();
    void sDoAction(const Action &action);
    void sAnimation();
    void sMovement();
    void sBoundingBox();
    void spwanPlayer();
    void sGravity();
    void sCollision();
    void sLifeSpan();
    void spawnBullet();
    void animationDirection();
    void QtAnimationSetUp(std::shared_ptr<Entity> e);
    void initTimerCcount();
    void updateTimer();
    void createFileReplay();
    bool inTheAir();
    void doAction(const Action &action);
    Vec2 gridToPixel(const Vec2 &gPos, std::shared_ptr<Entity> e);

    void onEnd();

public:
    Scene_InGame(const std::string &levelPathVar, GameEngine *game_engine = nullptr, bool isReplay = false);

    void sRender();
};