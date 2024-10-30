#include "Scene_Menu.h"

#include "Scene_InGame.h"
#include "GameEngine.h"

#include <iostream>
#include <SFML/Graphics.hpp>

Scene_Menu::Scene_Menu(std::vector<std::string> levPaths, GameEngine *gameEngine)
    : Scene(gameEngine), levelPaths(levPaths)
{
    init();
}

void Scene_Menu::init()
{
    registerAction(sf::Keyboard::Scan::Scancode::Escape, "QUIT");
    registerAction(sf::Keyboard::Scan::Scancode::W, "UP");
    registerAction(sf::Keyboard::Scan::Scancode::S, "DOWN");
    registerAction(sf::Keyboard::Scan::Scancode::Enter, "ENTER");

    initMenuObject();
}

void Scene_Menu::initMenuObject()
{
    float i = 0;
    for (std::string &str : menuStrings)
    {
        sf::Text text;
        text.setString(str);
        text.setFont(game_engine->getAssets().getFont("PublicPixel"));
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(40);
        text.setPosition({10, 200 + i});
        i = i + 100;
        menuTexts.push_back(text);
    }
    menuTexts.at(0).setFillColor(sf::Color::White);

    sf::Text text;
    text.setString(title);
    text.setFont(game_engine->getAssets().getFont("GarfieldSans"));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(100);
    text.setPosition({20, 10});
    menuTexts.push_back(text);

    sf::Text text2;
    text2.setString(help);
    text2.setFont(game_engine->getAssets().getFont("PublicPixel"));
    text2.setFillColor(sf::Color::Black);
    text2.setCharacterSize(20);
    text2.setPosition({40, 770});
    menuTexts.push_back(text2);

    staticGar = entities.addEntity("staticGarMenu");
    staticGar->addComponent<CAnimation>(game_engine->getAssets().getAnimation("staticGarMenuAn"));
    staticGar->addComponent<CTransform>(Vec2{1000, 510}, Vec2{0, 0});

    anGar = entities.addEntity("anGarMenu");
    anGar->addComponent<CAnimation>(game_engine->getAssets().getAnimation("menuGarAn"));
    anGar->addComponent<CTransform>(Vec2{menuTexts.at(selectedMenuIndex).getGlobalBounds().getPosition().x + menuTexts.at(selectedMenuIndex).getGlobalBounds().width + 50, menuTexts.at(selectedMenuIndex).getGlobalBounds().getPosition().y + menuTexts.at(selectedMenuIndex).getGlobalBounds().height / 2});

    ambiantSound.setBuffer(game_engine->getAssets().getSoundBuffer("ambientSound"));
    ambiantSound.setLoop(true);
    ambiantSound.setVolume(20);
    ambiantSound.play();
}

void Scene_Menu::sRender()
{
    game_engine->getWindow().clear(sf::Color(255, 162, 41));

    for (sf::Text &text : menuTexts)
    {
        game_engine->getWindow().draw(text);
    }
    game_engine->getWindow().draw(staticGar->getComponent<CAnimation>().animation.getSprite());
    game_engine->getWindow().draw(anGar->getComponent<CAnimation>().animation.getSprite());

    game_engine->getWindow().display();
}

void Scene_Menu::sDoAction(const Action &action)
{
    if (action.getType() == "START")
    {
        if (action.getName() == "QUIT")
        {
            game_engine->quit();
        }
        else if (action.getName() == "UP" || action.getName() == "DOWN")
        {
            moveSelectedItems(action.getName());
            sf::Sound s(game_engine->getAssets().getSoundBuffer("MenuChanging"));
            s.play();
            while (s.getStatus() == sf::Sound::Status::Playing)
                ;
        }
        else if (action.getName() == "ENTER")
        {
            onEnd();
        }
    }
}

void Scene_Menu::sAnimation()
{
    staticGar->getComponent<CAnimation>().animation.getSprite().setPosition(staticGar->getComponent<CTransform>().pos.x, staticGar->getComponent<CTransform>().pos.y);

    anGar->getComponent<CAnimation>().animation.update();
    anGar->getComponent<CAnimation>().animation.getSprite().setPosition(anGar->getComponent<CTransform>().pos.x, anGar->getComponent<CTransform>().pos.y);
}

void Scene_Menu::moveSelectedItems(const std::string &direction)
{
    size_t t = (direction == "UP") ? -1 : 1;

    menuTexts.at(selectedMenuIndex).setFillColor(sf::Color::Black);
    selectedMenuIndex = (selectedMenuIndex + t) % 4;
    menuTexts.at(selectedMenuIndex).setFillColor(sf::Color::White);

    anGar->getComponent<CTransform>().pos = Vec2{menuTexts.at(selectedMenuIndex).getGlobalBounds().getPosition().x + menuTexts.at(selectedMenuIndex).getGlobalBounds().width + 50, menuTexts.at(selectedMenuIndex).getGlobalBounds().getPosition().y + menuTexts.at(selectedMenuIndex).getGlobalBounds().height / 2};
}

void Scene_Menu::onEnd()
{
    if (selectedMenuIndex == 3)
    {
        game_engine->quit();
    }
    if (selectedMenuIndex == 2)
    {
        game_engine->loadReplay("../../replays/replay0.txt");
    }
    else
    {
        sf::Sound s(game_engine->getAssets().getSoundBuffer("coolSel"));
        s.play();
        while (s.getStatus() == sf::Sound::Status::Playing)
            ;
        game_engine->changeScene("gameplay", std::make_shared<Scene_InGame>(levelPaths.at(selectedMenuIndex), game_engine));
    }
}

void Scene_Menu::update()
{
    entities.update();
    sAnimation();
    sRender();
}
