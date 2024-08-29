#include <string>

#include "Scene_Menu.h"
#include "GameEngine.h"


void GameEngine::init(const std::string &config)
{
    changeScene("menu",std::make_shared<Scene_Menu>(this));

    window.create(sf::VideoMode({1400,800}),"Assignement 3");
    window.setFramerateLimit(60);

}

bool GameEngine::isRunning()
{
    return running && window.isOpen();
}

void GameEngine::changeScene(const std::string & sceneName, std::shared_ptr<Scene> scene,bool endCurrentScene)
{
    current_scene= sceneName;
    scenes[sceneName]= scene;
}

GameEngine::GameEngine(const std::string &config)
{
    init(config);
}

void GameEngine::run()
{   
    while (isRunning())
    {
        sUserInput();
        update(); 
    }  
}

void GameEngine::update()
{
    scenes[current_scene]->update();
}

void GameEngine::sUserInput()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            running = false;
        }
    }
    
}