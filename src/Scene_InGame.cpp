#include "Scene_InGame.h"

#include <iostream>
#include <algorithm>

#include <sstream>
#include <fstream>

#include "GameEngine.h"

Scene_InGame::Scene_InGame(const std::string &levelPathVar, GameEngine *gameEngine)
    : Scene(gameEngine), levelPath(levelPathVar)
{
    init();
}

void Scene_InGame::init()
{
    registerAction(sf::Keyboard::Scan::Scancode::A, "LEFT");
    registerAction(sf::Keyboard::Scan::Scancode::D, "RIGHT");
    registerAction(sf::Keyboard::Scan::Scancode::G, "DSPGRID");

    griTtext.setFont(game_engine->getAssets().getFont("Arial"));
    griTtext.setCharacterSize(10);

    loadLevel(levelPath);
}

void Scene_InGame::loadLevel(const std::string &filename)
{

    std::ifstream levelFile;

    levelFile.open(filename);

    std::string line;
    std::string param;

    while (std::getline(levelFile, line))
    {
        std::getline(std::stringstream(line), param, ' ');

        if (param == "Tile" || param == "Dec")
        {
            std::vector<std::string> par;
            std::stringstream ssline(line);
            while (std::getline(ssline, param, ' '))
            {
                par.push_back(param);
            }
            auto e = entities.addEntity(par.at(0));

            e->addComponent<CAnimation>(game_engine->getAssets().getAnimation(par.at(1)));
            Vec2 gridPos = Vec2{std::stof(par.at(2)), std::stof(par.at(3))};
            Vec2 pixPos = gridToPixel(gridPos, e);
            e->addComponent<CTransform>(pixPos);
        }
    }
}

void Scene_InGame::sDoAction(const Action &action)
{
    if (action.getType() == "START")
    {
        if (action.getName() == "LEFT")
        {
            t = t - 20;
            std::cout << "Q";
        }
        else if (action.getName() == "RIGHT")
        {
            t = t + 20;
            std::cout << "D";
        }
        else if (action.getName() == "DSPGRID")
        {
            drawGrid = !drawGrid;
        }
    }
}

Vec2 Scene_InGame::gridToPixel(Vec2 &gPos, std::shared_ptr<Entity> e)
{
    float x = gPos.x * gridSize.x + e->getComponent<CAnimation>().animation.getSprite().getTexture()->getSize().x / 2;
    float y = height() - gPos.y * gridSize.y - e->getComponent<CAnimation>().animation.getSprite().getTexture()->getSize().y / 2;
    return Vec2(x, y);
}

void Scene_InGame::onEnd()
{
}

void Scene_InGame::sRender()
{
    game_engine->getWindow().clear(sf::Color(0, 162, 0));

    // auto & pPos = 1;
    float windowCenterX = std::max(game_engine->getWindow().getSize().x / 2.0f, t);
    sf::View view = game_engine->getWindow().getView();
    view.setCenter(windowCenterX, game_engine->getWindow().getSize().y - view.getCenter().y);
    game_engine->getWindow().setView(view);

    if (drawTextures)
    {
        for (auto e : entities.getEntities())
        {
            e->getComponent<CAnimation>().animation.getSprite().setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
            game_engine->getWindow().draw(e->getComponent<CAnimation>().animation.getSprite());
        }
    }

    if (drawGrid)
    {
        float leftX = game_engine->getWindow().getView().getCenter().x - width() / 2;
        float rightX = leftX + width() + gridSize.x;
        float nextGrid = leftX - ((int)leftX % (int)gridSize.x);

        for (float x = nextGrid; x < rightX; x += gridSize.x)
        {
            drawLine(Vec2{x, 0}, Vec2{-1, (float)height()});
        }

        for (float y = 0; y < height(); y += gridSize.y)
        {
            drawLine(Vec2{leftX, height() - y}, Vec2{(float)width(), -1});
            for (float x = nextGrid; x < rightX; x += gridSize.x)
            {
                std::string xCell = std::to_string((int)x / (int)gridSize.x);
                std::string yCell = std::to_string((int)y / (int)gridSize.y);
                griTtext.setString("(" + xCell + "," + yCell + ")");
                griTtext.setPosition(x + 3, height() - y - gridSize.y + 2);
                game_engine->getWindow().draw(griTtext);
            }
        }
    }

    game_engine->getWindow().display();
}

void Scene_InGame::update()
{
    entities.update();
    sRender();
}