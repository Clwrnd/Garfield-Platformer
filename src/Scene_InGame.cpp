#include "Scene_InGame.h"

#include<iostream>
#include<algorithm>

#include "GameEngine.h"

Scene_InGame::Scene_InGame(const std::string &levelPathVar, GameEngine *gameEngine)
    : Scene(gameEngine), levelPath(levelPathVar)
{
    
    init();
}

void Scene_InGame::init()
{
    registerAction(sf::Keyboard::Q ,"LEFT");
    registerAction(sf::Keyboard::D,"RIGHT");
    registerAction(sf::Keyboard::G, "DSPGRID");


    griTtext.setFont(game_engine->getAssets().getFont("Arial"));
    griTtext.setCharacterSize(10);
}

void Scene_InGame::loadLevel(const std::string &filename)
{
}



void Scene_InGame::sDoAction(const Action &action)
{
    if(action.getType() == "START")
    {
        if(action.getName() == "LEFT" )
        {
            t=t-20;
            std::cout<<"Q";
        } 
        else if (action.getName() == "RIGHT")
        {
            t=t+20;
            std::cout<<"D";
        } 
        else if (action.getName() == "DSPGRID")
        {
            drawGrid = !drawGrid;
        }

    }
}

void Scene_InGame::onEnd()
{
}

void Scene_InGame::sRender() 
{
    game_engine->getWindow().clear(sf::Color(0, 162, 0));

    //auto & pPos = 1;
    float windowCenterX = std::max(game_engine->getWindow().getSize().x/2.0f,t);
    sf::View view = game_engine->getWindow().getView();
    view.setCenter(windowCenterX,game_engine->getWindow().getSize().y-view.getCenter().y);
    game_engine->getWindow().setView(view);

    

    if (drawGrid)
    {
    float leftX = game_engine->getWindow().getView().getCenter().x - width() / 2;    
    float rightX = leftX + width() + gridSize.x ;
    float nextGrid = leftX - ((int)leftX % (int)gridSize.x);

    for (float x = nextGrid; x < rightX; x+=gridSize.x)
    {
        drawLine(Vec2{x,0},Vec2{-1,(float)height()});
    }

    for(float y = 0; y<height();y+=gridSize.y)
    {
        drawLine(Vec2{leftX,height()-y},Vec2{(float)width(),-1});
        for(float x = nextGrid;x<rightX;x+=gridSize.x)
        {
            std::string xCell = std::to_string((int)x / (int)gridSize.x);
            std::string yCell = std::to_string((int)y / (int)gridSize.y);
            griTtext.setString("(" + xCell +","+ yCell+ ")");
            griTtext.setPosition(x+3,height()-y-gridSize.y+2);
            game_engine->getWindow().draw(griTtext);
        }
    }



    }
    game_engine->getWindow().display();
}

void Scene_InGame::update()
{

    sRender();
}