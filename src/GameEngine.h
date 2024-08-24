#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Assets.h"

class GameEngine
{
private:
    std::map<std::string, Scene> scenes;
    sf::RenderWindow window;
    Assets assets;
    std::string current_scene;
    bool running;

    Scene *currentScene();
    void init(const std::string &config);

public:
    GameEngine(const std::string &config);
    Assets &getAssets();
    sf::RenderWindow &window();
    void update();
    void quit();
    void sUserInput();
    void run();
    void changeScene(Scene scene);
    
};