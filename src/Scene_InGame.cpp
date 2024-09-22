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
    registerAction(sf::Keyboard::Scan::Scancode::W, "JUMP");
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
    std::string typeS;
    std::vector<std::string> paramVec;

    while (std::getline(levelFile, line))
    {
        std::getline(std::stringstream(line), typeS, ' ');
        paramVec.clear();

        std::stringstream ssline(line);
        while (std::getline(ssline, param, ' '))
        {
            paramVec.push_back(param);
        }

        if (typeS == "Tile" || typeS == "Dec")
        {

            auto e = entities.addEntity(typeS);

            e->addComponent<CAnimation>(game_engine->getAssets().getAnimation(paramVec.at(1)));
            Vec2 gridPos = Vec2{std::stof(paramVec.at(2)), std::stof(paramVec.at(3))};
            Vec2 pixPos = gridToPixel(gridPos, e);
            e->addComponent<CTransform>(pixPos);

            if (typeS == "Tile")
            {
                e->addComponent<CBoundingBox>(e->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().x,
                                              e->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().y);
            }
        }
        else if (typeS == "Player")
        {
            plConfig.X = std::stof(paramVec.at(1));
            plConfig.Y = std::stof(paramVec.at(2));
            plConfig.CX = std::stof(paramVec.at(3));
            plConfig.CY = std::stof(paramVec.at(4));
            plConfig.SPEED = std::stof(paramVec.at(5));
            plConfig.JUMP = std::stof(paramVec.at(6));
            plConfig.MAXSPEED = std::stof(paramVec.at(7));
            plConfig.GRAVITY = std::stof(paramVec.at(8));
            plConfig.WEAPON = paramVec.at(9);
        }
    }
}

void Scene_InGame::spwanPlayer()
{
    player = entities.addEntity("player");
    Vec2 pos{plConfig.X, plConfig.Y};
    player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
    player->addComponent<CTransform>(gridToPixel(Vec2{plConfig.X, plConfig.Y}, player), Vec2{plConfig.SPEED, 0});
    player->addComponent<CBoundingBox>(plConfig.CX, plConfig.CY);
    player->addComponent<CInput>();
    player->addComponent<CGravity>(plConfig.GRAVITY);
}

Vec2 Scene_InGame::gridToPixel(const Vec2 &gPos, std::shared_ptr<Entity> e)
{
    float x = gPos.x * gridSize.x + e->getComponent<CAnimation>().animation.getSprite().getTexture()->getSize().x / 2;
    float y = height() - gPos.y * gridSize.y - e->getComponent<CAnimation>().animation.getSprite().getTexture()->getSize().y / 2;
    return Vec2(x, y);
}

void Scene_InGame::sGravity()
{
    if (true)
    {
        player->getComponent<CTransform>().speed.y += player->getComponent<CGravity>().strenght;
    }
}

void Scene_InGame::sDoAction(const Action &action)
{
    if (action.getType() == "START")
    {
        if (action.getName() == "LEFT")
        {
            if (!player->getComponent<CInput>().right)
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
                player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
            }
            else
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
            }

            player->getComponent<CInput>().left = true;
        }
        else if (action.getName() == "RIGHT")
        {
            if (!player->getComponent<CInput>().left)
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
            }
            else
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
            }

            player->getComponent<CInput>().right = true;
        }
        else if (action.getName() == "JUMP")
        {
            player->getComponent<CInput>().up = true;
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
    else
    {
        if (action.getName() == "LEFT")
        {
            if (!player->getComponent<CInput>().right)
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
            }
            else
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
            }

            player->getComponent<CInput>().left = false;
        }
        else if (action.getName() == "RIGHT")
        {
            if (!player->getComponent<CInput>().left)
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
            }
            else
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
                player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
            }

            player->getComponent<CInput>().right = false;
        }
        else if (action.getName() == "JUMP")
        {
            player->getComponent<CInput>().up = false;
        }
    }
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

void Scene_InGame::sAnimation()
{
    for (auto e : entities.getEntities())
    {
        if (e->hasComponent<CAnimation>())
        {
            e->getComponent<CAnimation>().animation.getSprite().setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
            e->getComponent<CAnimation>().animation.update();
        }
    }
}

void Scene_InGame::sMovement()
{
    player->getComponent<CTransform>().previousPos = player->getComponent<CTransform>().pos;

    player->getComponent<CTransform>().pos.y += player->getComponent<CTransform>().speed.y;

    if (player->getComponent<CInput>().right)
    {
        player->getComponent<CTransform>().pos.x += player->getComponent<CTransform>().speed.x;
    }
    if (player->getComponent<CInput>().left)
    {
        player->getComponent<CTransform>().pos.x -= player->getComponent<CTransform>().speed.x;
    }
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

void Scene_InGame::onEnd()
{
}

void Scene_InGame::update()
{
    entities.update();
    sGravity();
    sMovement();
    sBoundingBox();
    sAnimation();
    sRender();
}