#pragma once
#include "Scene.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Scene_Menu : public Scene
{
protected:
    std::string title = "GARFIELD Platformer";
    std::vector<std::string> menuStrings = {"-LEVEL 1", "-LEVEL 2", "-LEVEL 3", "LEAVE"};
    std::string help = "COMMAND: USUAL KEYS ( WASD, ZQSD ... )";
    std::vector<sf::Text> menuTexts;
    std::vector<std::string> levelPaths;
    std::shared_ptr<Entity> staticGar;
    std::shared_ptr<Entity> anGar;
    sf::Font font;
    sf::Sound ambiantSound;
    size_t selectedMenuIndex = 0;

    void init();
    void initMenuObject();
    void update();
    void moveSelectedItems(const std::string &direction);
    void onEnd();
    void sDoAction(const Action &action);
    void sAnimation();
    
public:
    Scene_Menu(std::vector<std::string> levPaths, GameEngine *game_engine = nullptr);

    void sRender();
};
