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

    float i=0;
    for (std::string  & str : menuStrings)
    {
        sf::Text text;  
        text.setString(str);
        text.setFont(game_engine->getAssets().getFont("GarfieldFont"));
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(75);
        text.setPosition({10,200+i});
        i=i+150;    
        menuTexts.push_back(text);
    }

    garAnim = entities.addEntity("gar");
    garAnim->getComponent<CAnimation>().animation = Animation("garf",game_engine->getAssets().getTexture("testGarT"),2,10);
    garAnim->addComponent<CTransform>(Vec2{800,600},Vec2{0,0},0);
}

void Scene_Menu::sRender() 
{
    game_engine->getWindow().clear(sf::Color(255,162,41));
    for(sf::Text & text : menuTexts)
    {
        game_engine->getWindow().draw(text); 
    }
    garAnim->getComponent<CAnimation>().animation.update();
    garAnim->getComponent<CAnimation>().animation.getSprite().setPosition(garAnim->getComponent<CTransform>().pos.x,garAnim->getComponent<CTransform>().pos.y);
    game_engine->getWindow().draw(garAnim->getComponent<CAnimation>().animation.getSprite()); 


    game_engine->getWindow().display();
}

void Scene_Menu::sDoAction(const Action & action)
{
    if(action.getName()=="QUIT")
    {
        onEnd();
    }
}



void Scene_Menu::onEnd()
{
    game_engine->quit();
}

void Scene_Menu::update()
{  
    entities.update();
    sRender();
}

