#include "Scene_Menu.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameEngine.h"

Scene_Menu::Scene_Menu(GameEngine * gameEngine)
    : Scene(gameEngine)
{
    init();
}

void Scene_Menu::init()
{
    registerAction(sf::Keyboard::Escape, "QUIT");
}

void Scene_Menu::sRender() 
{
    
}

void Scene_Menu::sDoAction(const Action & action)
{
    if(action.getName()=="QUIT")
    {
        onEnd();
    }
}

void Scene_Menu::doAction(const Action & action)
{
    sDoAction(action);
}

void Scene_Menu::onEnd()
{
    game_engine->quit();
}

void Scene_Menu::update()
{   
    sRender();
}

