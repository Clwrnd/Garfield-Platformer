#pragma once

#include "Vec2.h"

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
    float ang = 0;

    CTransform() {};
    CTransform(const Vec2 &posVar, const Vec2 &speedVar, float angVar)
        : pos(posVar), speed(speedVar), ang(angVar)
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
    CInput() {}
};

class CBoundingBox : public Component
{
public:
    CBoundingBox() {}
};

class CAnimation : public Component
{
public:
    CAnimation() {}
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
