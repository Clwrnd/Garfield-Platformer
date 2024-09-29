#pragma once

#include "Vec2.h"
#include "Animation.h"

class Component
{
public:
    bool has = false;
};

class CTransform : public Component
{
public:
    Vec2 pos = {0, 0};
    Vec2 previousPos = {0, 0};
    Vec2 speed = {0, 0};
    float angle = 0;

    CTransform() {};
    CTransform(const Vec2 &posVar)
        : pos(posVar), previousPos(posVar)
    {
    }
    CTransform(const Vec2 &posVar, const Vec2 &speedVar)
        : pos(posVar), speed(speedVar), previousPos(posVar)
    {
    }
    CTransform(const Vec2 &posVar, const Vec2 &speedVar, float angVar)
        : pos(posVar), speed(speedVar), previousPos(posVar), angle(angVar)
    {
    }
};

class CLifespan : public Component
{
public:
    int remaining = 0;
    int total = 0;

    CLifespan() {};
    CLifespan(int rm, int tl)
        : remaining(rm), total(tl)
    {
    }
};

class CInput : public Component
{
public:
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;

    CInput() {}
};

class CMovement : public Component
{
public:
    bool isJumping = false;
    bool isRight = false;
    bool isLeft = false;

    bool wasJumping = false;
    bool wasRight = false;
    bool wasLeft = false;

    CMovement() {}
};

class CBoundingBox : public Component
{
public:
    sf::RectangleShape cb;
    float width;
    float height;
    CBoundingBox() {}
    CBoundingBox(float w, float h)
        : cb(sf::Vector2(w - 1, h - 1)), width(w), height(h)
    {
        cb.setOutlineThickness(1);
        cb.setOutlineColor(sf::Color::Black);
        cb.setFillColor(sf::Color(255, 255, 255, 0));
        cb.setOrigin(w / 2, h / 2);
    }
};

class CAnimation : public Component
{
public:
    Animation animation;

    CAnimation() {}
    CAnimation(Animation animationVar)
        : animation(animationVar)
    {
    }
};

class CGravity : public Component
{
public:
    float strenght;
    CGravity() {}
    CGravity(float strenghtVar)
        : strenght(strenghtVar)
    {
    }
};

class CState : public Component
{
public:
    CState() {}
};
