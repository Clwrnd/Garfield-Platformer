#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>

class Scene_Menu: public Scene
{
protected:
    std::string title = "GARFIELD Platformer";
    std::vector<std::string> menuStrings = {"-LEVEL 1", "-LEVEL 2", "-LEVEL 3", "LEAVE"};
    std::vector<sf::Text> menuTexts;
    std::vector<std::string> levelPaths;
    std::shared_ptr<Entity> staticGar;
    std::shared_ptr<Entity> anGar;
    sf::Font font;
    size_t selectedMenuIndex = 0;

    void init();
    void update();
    void onEnd(size_t selectedItem);
    void sDoAction(const Action & action);
    void initMenuObject();
    void sAnimation();
    void moveSelectedItems(const std::string & direction);

public:    
    Scene_Menu(GameEngine * game_engine = nullptr);

    void sRender();
};
