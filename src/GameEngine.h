#pragma once

#include "Scene.h"
#include "Assets.h"

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine
{
protected:
    std::string current_scene;
    sf::RenderWindow window;
    SceneMap scenes;
    Assets assets;

    bool running = true;

    void init(const std::string &config);
    void update();
    void sUserInput();

    std::shared_ptr<Scene> getCurrent_Scene();

public:
    GameEngine(const std::string &config);
    const Assets &getAssets() const;
    sf::RenderWindow &getWindow();
    void quit();
    void run();
    void changeScene(const std::string &sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false);
    void changeScene(const std::string &sceneName, bool endCurrentScene = false);
    const std::vector<std::string> readConfigFile(const std::string &path);
    void loadAssets(const std::string &path);
    bool isRunning();
};