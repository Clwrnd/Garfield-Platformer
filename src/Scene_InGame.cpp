#include "Scene_InGame.h"

#include<iostream>
#include "GameEngine.h"

Scene_InGame::Scene_InGame(const std::string &levelPathVar, GameEngine *gameEngine)
    : Scene(gameEngine), levelPath(levelPathVar)
{
    init();
}

void Scene_InGame::init()
{
}

void Scene_InGame::loadLevel(const std::string &filename)
{
}



void Scene_InGame::sDoAction(const Action &action)
{
}

void Scene_InGame::onEnd()
{
}

void Scene_InGame::sRender() 
{
    game_engine->getWindow().clear(sf::Color(0, 162, 0));
    if (drawGrid)
    {
        std::cout<< "hey";
        drawLine(Vec2{0, 0}, Vec2{1000,10});
    }
    game_engine->getWindow().display();
}

void Scene_InGame::update()
{
    sRender();
}