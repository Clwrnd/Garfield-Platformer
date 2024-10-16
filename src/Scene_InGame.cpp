#include "Scene_InGame.h"

#include <iostream>
#include <algorithm>

#include <sstream>
#include <fstream>

#include "Physics.h"
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
    registerAction(sf::Keyboard::Scan::Scancode::Space, "FIRE");
    registerAction(sf::Keyboard::Scan::Scancode::P, "PAUSE");

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
                e->addComponent<CDestructable>(std::stoi(paramVec.at(4)));
                if (paramVec.at(1) == "QtileAA")
                {
                    // A compléter
                }
            }
        }
        else if (typeS == "Player")
        {
            plConfig.X = std::stof(paramVec.at(1));
            plConfig.Y = std::stof(paramVec.at(2));
            plConfig.CX = std::stof(paramVec.at(3));
            plConfig.CY = std::stof(paramVec.at(4));
            plConfig.SPEED = std::stof(paramVec.at(5));
            plConfig.JUMP = -std::stof(paramVec.at(6));
            plConfig.MAXSPEED = std::stof(paramVec.at(7));
            plConfig.GRAVITY = std::stof(paramVec.at(8));
            plConfig.WEAPON = paramVec.at(9);
            plConfig.BULLETS = std::stof(paramVec.at(10));
            plConfig.BULLETL = std::stof(paramVec.at(11));
            plConfig.BULLETA = std::stof(paramVec.at(12));
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
    player->addComponent<CMovement>();
}

Vec2 Scene_InGame::gridToPixel(const Vec2 &gPos, std::shared_ptr<Entity> e)
{
    float x = gPos.x * gridSize.x + e->getComponent<CAnimation>().animation.getSprite().getTextureRect().width / 2;
    float y = height() - gPos.y * gridSize.y - e->getComponent<CAnimation>().animation.getSprite().getTextureRect().height / 2;
    return Vec2(x, y);
}

void Scene_InGame::sGravity()
{
    if (std::abs(player->getComponent<CTransform>().speed.y + player->getComponent<CGravity>().strenght) < plConfig.MAXSPEED)
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
            player->getComponent<CInput>().left = true;
            player->getComponent<CMovement>().isLeft = true;
        }
        else if (action.getName() == "RIGHT")
        {
            player->getComponent<CInput>().right = true;
            player->getComponent<CMovement>().isRight = true;
        }
        else if (action.getName() == "JUMP" && !inTheAir())
        {
            player->getComponent<CTransform>().speed.y = plConfig.JUMP;
            player->getComponent<CInput>().up = true;
            player->getComponent<CMovement>().isJumping = true;
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
        else if (action.getName() == "FIRE")
        {
            spawnBullet();
        }
        else if (action.getName() == "PAUSE")
        {
            paused = !paused;
        }
    }
    else
    {
        if (action.getName() == "LEFT")
        {
            player->getComponent<CInput>().left = false;
            player->getComponent<CMovement>().isLeft = false;
        }
        else if (action.getName() == "RIGHT")
        {
            player->getComponent<CInput>().right = false;
            player->getComponent<CMovement>().isRight = false;
        }
        else if (action.getName() == "JUMP")
        {
            player->getComponent<CInput>().up = false;
            if (player->getComponent<CTransform>().speed.y < 0)
                player->getComponent<CTransform>().speed.y = 2;
        }
    }
}

void Scene_InGame::sRender()
{
    game_engine->getWindow().clear(sf::Color(11, 103, 146));

    auto &pPos = player->getComponent<CTransform>().pos;
    float windowCenterX = std::max(game_engine->getWindow().getSize().x / 2.0f, pPos.x);
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
    animationDirection();

    for (auto e : entities.getEntities())
    {
        if (e->hasComponent<CAnimation>())
        {
            e->getComponent<CAnimation>().animation.getSprite().rotate(e->getComponent<CTransform>().angle);
            e->getComponent<CAnimation>().animation.getSprite().setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
            e->getComponent<CAnimation>().animation.update();
        }
    }

    player->getComponent<CMovement>().wasJumping = player->getComponent<CMovement>().isJumping;
    player->getComponent<CMovement>().wasLeft = player->getComponent<CMovement>().isLeft;
    player->getComponent<CMovement>().wasRight = player->getComponent<CMovement>().isRight;
}

void Scene_InGame::sLifeSpan()
{
    for (auto e : entities.getEntities("Tile"))
    {
        if (e->hasComponent<CAnimation>() && e->getComponent<CAnimation>().animation.hasEndend() && !e->getComponent<CAnimation>().animation.isRepeating())
        {
            e->destroy();
        }
    }
    for (auto e : entities.getEntities("bullet"))
    {
        e->getComponent<CLifespan>().remaining--;
        if (e->getComponent<CLifespan>().remaining == 0)
        {
            e->destroy();
        }
    }
}

void Scene_InGame::spawnBullet()
{
    auto e = entities.addEntity("bullet");
    e->addComponent<CAnimation>(game_engine->getAssets().getAnimation(plConfig.WEAPON));
    Vec2 pos{player->getComponent<CTransform>().pos.x, player->getComponent<CTransform>().pos.y};

    Vec2 spe{plConfig.BULLETS * player->getComponent<CAnimation>().animation.getSprite().getScale().x, 0};
    e->addComponent<CTransform>(pos, spe, plConfig.BULLETA);
    e->addComponent<CLifespan>(plConfig.BULLETL, plConfig.BULLETL);
    e->addComponent<CBoundingBox>(e->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().x,
                                  e->getComponent<CAnimation>().animation.getSprite().getTextureRect().getSize().y);
}

void Scene_InGame::sMovement()
{
    player->getComponent<CTransform>().previousPos = player->getComponent<CTransform>().pos;

    player->getComponent<CTransform>().pos.y += player->getComponent<CTransform>().speed.y;

    if (player->getComponent<CInput>().right)
    {
        player->getComponent<CTransform>().pos.x += player->getComponent<CTransform>().speed.x;
    }
    if (player->getComponent<CInput>().left && player->getComponent<CTransform>().pos.x - player->getComponent<CTransform>().speed.x > 0)
    {
        player->getComponent<CTransform>().pos.x -= player->getComponent<CTransform>().speed.x;
    }
    if (player->getComponent<CInput>().up)
    {
        player->getComponent<CTransform>().pos.y += player->getComponent<CTransform>().speed.y;
    }

    for (auto e : entities.getEntities("bullet"))
    {
        e->getComponent<CTransform>().pos.x += e->getComponent<CTransform>().speed.x;
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

void Scene_InGame::sCollision()
{
    for (auto e : entities.getEntities("Tile"))
    {
        Vec2 ovV = Physics::getOverlap(player, e);

        if (ovV.isPositiv())
        {
            Vec2 ovVPr = Physics::getPreviousOverlap(player, e);
            if (player->getComponent<CTransform>().pos.y > player->getComponent<CTransform>().previousPos.y && ovVPr.x > 0)
            {
                player->getComponent<CTransform>().speed.y = 0;
                player->getComponent<CTransform>().pos.y -= ovV.y;
                player->getComponent<CMovement>().isJumping = false;
            }
            else if (player->getComponent<CTransform>().pos.x > player->getComponent<CTransform>().previousPos.x && ovVPr.y > 0)
            {
                player->getComponent<CTransform>().pos.x -= ovV.x;
            }
            else if (player->getComponent<CTransform>().pos.x < player->getComponent<CTransform>().previousPos.x && ovVPr.y > 0)
            {
                player->getComponent<CTransform>().pos.x += ovV.x;
            }
            else if (player->getComponent<CTransform>().pos.y < player->getComponent<CTransform>().previousPos.y && ovVPr.x > 0)
            {
                player->getComponent<CTransform>().speed.y = 0;
                player->getComponent<CTransform>().pos.y += ovV.y;
                if (e->getComponent<CDestructable>().isDestructable)
                {
                    e->removeComponent<CBoundingBox>();
                    e->addComponent<CAnimation>(game_engine->getAssets().getAnimation("Explosion"));
                    e->getComponent<CAnimation>().animation.mmkNonRepeating();
                }
                else if (true)
                {
                    // A compléter
                }
            }
        }

        for (auto bullet : entities.getEntities("bullet"))
        {
            if (Physics::getOverlap(bullet, e).isPositiv())
            {
                if (e->getComponent<CDestructable>().isDestructable)
                {
                    e->removeComponent<CBoundingBox>();
                    e->addComponent<CAnimation>(game_engine->getAssets().getAnimation("Explosion"));
                    e->getComponent<CAnimation>().animation.mmkNonRepeating();
                }

                bullet->destroy();
            }
        }
    }
}

void Scene_InGame::animationDirection()
{
    // a real nightmare, It must have an easier way to implement this but I didn't found it so ...

    if (player->getComponent<CMovement>().isJumping && !player->getComponent<CMovement>().wasJumping)
    {

        if (player->getComponent<CAnimation>().animation.getSprite().getScale().x == -1)
        {
            player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("JumpGar"));
            player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
        }
        else
        {
            player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("JumpGar"));
        }
    }
    if (!player->getComponent<CMovement>().isJumping && player->getComponent<CMovement>().wasJumping)
    {
        if (player->getComponent<CMovement>().isRight)
        {
            player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
            player->getComponent<CAnimation>().animation.getSprite().setScale(1, 1);
        }
        else if (player->getComponent<CMovement>().isLeft)
        {
            player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
            player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
        }
        else
        {
            if (player->getComponent<CAnimation>().animation.getSprite().getScale().x == -1)
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
                player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
            }
            else
            {
                player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
            }
        }
    }
    if (player->getComponent<CMovement>().isJumping && player->getComponent<CMovement>().wasJumping)
    {
        if (player->getComponent<CMovement>().isLeft && !player->getComponent<CMovement>().wasLeft)
        {
            player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
        }
        if (player->getComponent<CMovement>().isRight && !player->getComponent<CMovement>().wasRight)
        {
            player->getComponent<CAnimation>().animation.getSprite().setScale(1, 1);
        }
    }
    if (player->getComponent<CMovement>().isRight && (!player->getComponent<CMovement>().wasRight || (player->getComponent<CMovement>().wasLeft && !player->getComponent<CMovement>().isLeft)) && !player->getComponent<CMovement>().isJumping)
    {
        player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
        player->getComponent<CAnimation>().animation.getSprite().setScale(1, 1);
    }
    if (player->getComponent<CMovement>().isLeft && (!player->getComponent<CMovement>().wasLeft || (player->getComponent<CMovement>().wasRight && !player->getComponent<CMovement>().isRight)) && !player->getComponent<CMovement>().isJumping)
    {
        player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("RunGar"));
        player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
    }
    if (!player->getComponent<CMovement>().isLeft && !player->getComponent<CMovement>().isRight && !player->getComponent<CMovement>().isJumping &&
        (player->getComponent<CMovement>().wasLeft || player->getComponent<CMovement>().wasRight || player->getComponent<CMovement>().wasJumping))
    {

        if (player->getComponent<CMovement>().wasLeft)
        {
            player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
            player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
        }
        if (player->getComponent<CMovement>().wasRight)
        {
            player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
            player->getComponent<CAnimation>().animation.getSprite().setScale(1, 1);
        }
    }
    if (player->getComponent<CMovement>().isLeft && player->getComponent<CMovement>().isRight && (!player->getComponent<CMovement>().wasLeft || !player->getComponent<CMovement>().wasRight) && !player->getComponent<CMovement>().isJumping)
    {
        player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("idleGar"));
    }
    if (player->getComponent<CMovement>().isLeft && !player->getComponent<CMovement>().wasJumping && player->getComponent<CMovement>().isJumping)
    {
        player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("JumpGar"));
        player->getComponent<CAnimation>().animation.getSprite().setScale(-1, 1);
    }
    if (player->getComponent<CMovement>().isRight && !player->getComponent<CMovement>().wasJumping && player->getComponent<CMovement>().isJumping)
    {
        player->addComponent<CAnimation>(game_engine->getAssets().getAnimation("JumpGar"));
        player->getComponent<CAnimation>().animation.getSprite().setScale(1, 1);
    }
}

bool Scene_InGame::inTheAir()
{
    bool toReturn = true;
    player->getComponent<CMovement>().isJumping = true;

    for (auto e : entities.getEntities("Tile"))
    {
        if (e->getComponent<CTransform>().pos.y - e->getComponent<CBoundingBox>().height / 2 == player->getComponent<CTransform>().pos.y + player->getComponent<CBoundingBox>().height / 2 &&
            e->getComponent<CTransform>().pos.x - (e->getComponent<CBoundingBox>().width / 2 + player->getComponent<CBoundingBox>().width) <= player->getComponent<CTransform>().pos.x && e->getComponent<CTransform>().pos.x + e->getComponent<CBoundingBox>().width / 2 + player->getComponent<CBoundingBox>().width >= player->getComponent<CTransform>().pos.x)
        {
            player->getComponent<CMovement>().isJumping = false;
            toReturn = false;
        }
    }
    return toReturn;
}

void Scene_InGame::onEnd()
{
}

void Scene_InGame::update()
{
    if (!paused)
    {
        entities.update();
        sGravity();
        sMovement();
        sCollision();
        sBoundingBox();
        sAnimation();
        sLifeSpan();
        sRender();
    }
    else
    {
        sRender();
    }
}