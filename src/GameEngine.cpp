#include "GameEngine.h"

#include <sstream>
#include <fstream>

#include <iostream>

#include "Scene_Menu.h"
#include "Scene_InGame.h"

GameEngine::GameEngine(const std::string &config)
{
    init(config);
}

void GameEngine::init(const std::string &config)
{
    // read all windows parameters and assets and levels files (not a very good idea
    // to mix a void and a return but it work and is coherent with the architecture )
    std::vector<std::string> levelsPaths = readConfigFile(config);
    window.setKeyRepeatEnabled(false);

    changeScene("menu", std::make_shared<Scene_Menu>(levelsPaths, this));
}

const std::vector<std::string> GameEngine::readConfigFile(const std::string &path)
{
    std::vector<std::string> levelsPath;

    std::ifstream configFile;

    configFile.open(path);

    std::string line;
    std::string param;

    while (std::getline(configFile, line))
    {
        std::getline(std::stringstream(line), param, ';');
        if (param == "Window")
        {
            std::vector<int> winPar;
            line.erase(0, 7);
            std::stringstream ssline(line);
            while (std::getline(ssline, param, ';'))
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
            line.erase(0, 10);
            levelsPath.push_back(line);
        }
    }
    configFile.close();
    return levelsPath;
}

void GameEngine::loadAssets(const std::string &path)
{
    std::ifstream assetsFile;
    assetsFile.open(path);

    std::string line;
    std::string param;
    std::string typeS;
    std::vector<std::string> paramVec;

    while (std::getline(assetsFile, line))
    {
        std::getline(std::stringstream(line), typeS, ';');
        paramVec.clear();

        std::stringstream ssline(line);
        while (std::getline(ssline, param, ';'))
        {
            paramVec.push_back(param);
        }

        if (typeS == "Texture")
        {
            assets.addTexture(paramVec.at(1), paramVec.at(2));
        }
        else if (typeS == "Animation")
        {
            Animation animation = Animation(paramVec.at(1), assets.getTexture(paramVec.at(2)), std::stoi(paramVec.at(3)), std::stoi(paramVec.at(4)));
            assets.addAnimation(paramVec.at(1), animation);
        }
        else if (typeS == "Font")
        {
            assets.addFont(paramVec.at(1), paramVec.at(2));
        }
        else if (typeS == "Sound")
        {
            assets.addSoundBuffer(paramVec.at(1), paramVec.at(2));
        }
    }

    assetsFile.close();
}

void GameEngine::changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
    if (endCurrentScene)
    {
        scenes.erase(current_scene);
    }

    current_scene = sceneName;
    scenes[sceneName] = scene;
}

void GameEngine::changeScene(const std::string &sceneName, bool endCurrentScene)
{
    if (endCurrentScene)
    {
        scenes.erase(current_scene);
    }
    current_scene = sceneName;
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
    getCurrent_Scene()->update();
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
            if (getCurrent_Scene()->getActionMap().find(event.key.scancode) == getCurrent_Scene()->getActionMap().end())
            {
                continue;
            }

            const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";
            const std::string actionName = getCurrent_Scene()->getActionMap().at(event.key.scancode);

            if (actionName == "QUIT" || actionName == "PAUSE" || !getCurrent_Scene()->isAReplay())
                getCurrent_Scene()->doAction(Action(actionName, actionType));
        }
    }
}

void GameEngine::loadReplay(const std::string &replayFilePath)
{
    replayActions.clear();

    std::ifstream replayFile;
    replayFile.open(replayFilePath);

    std::string line;
    std::string param;

    unsigned long f;
    std::string type, name;
    std::string levelFile;

    std::getline(replayFile, line);
    levelFile = line;

    while (std::getline(replayFile, line))
    {
        std::stringstream ssline(line);
        std::vector<std::string> pars;
        while (std::getline(ssline, param, ';'))
        {
            pars.emplace_back(param);
        }
        replayActions.push_back(Action(pars.at(2), pars.at(1), std::stoi(pars.at(0))));
    }
    replayFile.close();

    changeScene("gameplay", std::make_shared<Scene_InGame>(levelFile, this, true));
    playReplay();
}

void GameEngine::playReplay()
{
    if (getCurrent_Scene()->isAReplay())
    {
        while (replayActions.front().getFrame() == getCurrent_Scene()->getCurrentFrame() && !replayActions.empty())
        {
            getCurrent_Scene()->doAction(replayActions.front());

            replayActions.erase(replayActions.begin());
        }
    }
}

void GameEngine::run()
{
    while (isRunning())
    {
        playReplay();
        update();
    }
}
