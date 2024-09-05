#include "GameEngine.h"

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

#include "Scene_Menu.h"

GameEngine::GameEngine(const std::string &config)
{
    init(config);
}

void GameEngine::init(const std::string &config)
{
    readConfigFile(config);
    changeScene("menu", std::make_shared<Scene_Menu>(this));
}

void GameEngine::readConfigFile(const std::string &path)
{
    std::ifstream configFile;

    configFile.open(path);

    std::string line;
    std::string param;

    while (std::getline(configFile, line))
    {
        std::getline(std::stringstream(line), param, ' ');
        if (param == "Window")
        {
            std::vector<int> winPar;
            line.erase(0, 7);
            std::stringstream ssline(line);
            while (std::getline(ssline, param, ' '))
            {
                winPar.push_back(std::stoi(param));
            }

            if (winPar.at(3))
            {
                window.create(sf::VideoMode({(unsigned int)winPar.at(0), (unsigned int)winPar.at(1)}), "Assignement 3", sf::Style::Fullscreen);
            }
            else
            {
                window.create(sf::VideoMode({(unsigned int)winPar.at(0), (unsigned int)winPar.at(1)}), "Assignement 3");
            }
            window.setFramerateLimit(winPar.at(2));
        }
        else if (param == "AssetsPath")
        {
            line.erase(0, 11);
            loadAssets(line);
        }
        else if (param == "LevelPath")
        {
            /* code */
        }
    }

    configFile.close();
}

void GameEngine::loadAssets(const std::string &path)
{
    std::ifstream assetsFile;
    assetsFile.open(path);

    std::string line;
    std::string param;
    std::string typeS;

    while (std::getline(assetsFile, line))
    {
        std::getline(std::stringstream(line), typeS, ' ');

        std::vector<std::string> paramVec;
        line.erase(0, 8);
        std::stringstream ssline(line);
        while (std::getline(ssline, param, ' '))
        {
            paramVec.push_back(param);
        }

        if (typeS == "Texture")
        {
            assets.addTexture(paramVec.at(0), paramVec.at(1));
        }
        else if (typeS == "Animation")
        {
            assets.addAnimation(Animation(paramVec.at(0),paramVec.at(2)));
        }
        else if (typeS == "Font")
        {
            assets.addFont(paramVec.at(0), paramVec.at(1));
        }
    }

    assetsFile.close();
}

void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
    current_scene = sceneName;
    scenes[sceneName] = scene;
}

std::shared_ptr<Scene> GameEngine::getCurrent_Scene()
{
    return scenes[current_scene];
}

sf::RenderWindow &GameEngine::getWindow()
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
            if (getCurrent_Scene()->getActionMap().find(event.key.code) == getCurrent_Scene()->getActionMap().end())
            {
                continue;
            }

            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

            getCurrent_Scene()->doAction(Action(getCurrent_Scene()->getActionMap().at(event.key.code), actionType));
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
