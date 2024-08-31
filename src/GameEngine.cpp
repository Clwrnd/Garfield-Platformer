#include "GameEngine.h"

#include <string>

#include "Scene_Menu.h"

GameEngine::GameEngine(const std::string &config)
{
    init(config);
}

void GameEngine::init(const std::string &config)
{
    window.create(sf::VideoMode({1400,800}),"Assignement 3");
    window.setFramerateLimit(60);

    assets.addFont("GarfieldFont","../../fonts/GarfieldSans-Regular.ttf");

    changeScene("menu",std::make_shared<Scene_Menu>(this));
}

void GameEngine::loadAssets(std::string & path)
{

}

void GameEngine::changeScene(const std::string & sceneName, std::shared_ptr<Scene> scene,bool endCurrentScene)
{
    current_scene= sceneName;
    scenes[sceneName]= scene;
}

std::shared_ptr<Scene> GameEngine::getCurrent_Scene()
{
    return scenes[current_scene];
}

sf::RenderWindow& GameEngine::getWindow()
{
    return window;  
}

const Assets &GameEngine::getAssets() const
{
    return assets;
}

bool GameEngine::isRunning()
{
    return running && window.isOpen();
}

void GameEngine::quit()
{
    running = false;
}


void GameEngine::update()
{
    sUserInput();
    getCurrent_Scene()->sRender();
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

        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            if (getCurrent_Scene()->getActionMap().find(event.key.code)==getCurrent_Scene()->getActionMap().end())
            {continue;}

            const std::string actionType = (event.type ==  sf::Event::KeyPressed) ? "START" : "END";

            getCurrent_Scene()->doAction(Action(getCurrent_Scene()->getActionMap().at(event.key.code),actionType));
        }
    }
    
}


void GameEngine::run()
{   
    while (isRunning())
    {
        update(); 
    }  
}
