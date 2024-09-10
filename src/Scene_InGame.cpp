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
   

   
    

    if (drawGrid)
    {
    game_engine->getWindow().clear(sf::Color(0, 162, 0));

    float leftX = game_engine->getWindow().getView().getCenter().x - width() / 2;    
    float rightX = leftX + width() + gridSize.x ;
    float nextGrid = leftX - ((int)leftX % (int)gridSize.x);

    for (float x = nextGrid; x < rightX; x+=gridSize.x)
    {
        drawLine(Vec2{x,0},Vec2{-1,height()});
    }

    for(float y = 0; y<height();y+=gridSize.y)
    {
        drawLine(Vec2{leftX,height()-y},Vec2{width(),-1});
    }

    }
    game_engine->getWindow().display();
}

void Scene_InGame::update()
{
    sRender();
}