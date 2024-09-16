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
    registerAction(sf::Keyboard::Scan::Scancode::C, "DSPCB");
    registerAction(sf::Keyboard::Scan::Scancode::T, "DSPTEXT");
    registerAction(sf::Keyboard::Scan::Scancode::Escape, "QUIT");

    griTtext.setFont(game_engine->getAssets().getFont("Arial"));
    griTtext.setCharacterSize(10);

    loadLevel(levelPath);
    spwanPlayer();
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

            if (par.at(0) == "Tile")
            {
                e->addComponent<CBoundingBox>(e->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().x,
                                              e->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().y);
            }
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
        else if (action.getName() == "DSPCB")
        {
            drawBoundingBox = !drawBoundingBox;
        }
        else if (action.getName() == "DSPTEXT")
        {
            drawTextures = !drawTextures;
        }
        else if (action.getName() == "QUIT")
        {
            sf::View view = game_engine->getWindow().getView();
            view.setCenter(game_engine->getWindow().getSize().x / 2.0f, game_engine->getWindow().getSize().y / 2.0f);
            game_engine->getWindow().setView(view);
            game_engine->changeScene("menu", true);
        }
    }
}

void Scene_InGame::sAnimation()
{
    for (auto e : entities.getEntities())
    {
        e->getComponent<CAnimation>().animation.getSprite().setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
        e->getComponent<CAnimation>().animation.update();
    }
}

void Scene_InGame::sMovement()
{
}

void Scene_InGame::sBoundingBox()
{
    for (auto e : entities.getEntities())
    {
        if (e->hasComponent<CBoundingBox>())
        {
            e->getComponent<CBoundingBox>().cb.setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
            e->getComponent<CAnimation>().animation.update();
        }
    }
}

void Scene_InGame::spwanPlayer()
{
    player = entities.addEntity("player");
    player->addComponent<CTransform>(Vec2{100, 100});
    player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
    player->addComponent<CBoundingBox>(player->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().x,
                                       player->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().y);
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
            game_engine->getWindow().draw(e->getComponent<CAnimation>().animation.getSprite());
        }
    }

    if (drawBoundingBox)
    {
        for (auto e : entities.getEntities())
        {
            if (e->hasComponent<CBoundingBox>())
            {
                game_engine->getWindow().draw(e->getComponent<CBoundingBox>().cb);
            }
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
    sMovement();
    sBoundingBox();
    sAnimation();
    sRender();
}