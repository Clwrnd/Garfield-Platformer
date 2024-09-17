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
    Vec2 speed = {0, 0};

    CTransform() {};
    CTransform(const Vec2 &posVar)
        : pos(posVar)
    {
    }
    CTransform(const Vec2 &posVar, const Vec2 &speedVar)
        : pos(posVar), speed(speedVar)
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
    CGravity() {}
};

class CState : public Component
{
public:
    CState() {}
};
