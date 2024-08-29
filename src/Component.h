#pragma once
#include "Vec2.h"

class Component
{
public:
    bool has = false;
};

class CTransform: public Component
{
public:
    Vec2 pos = {0, 0};
    Vec2 speed = {0, 0};
    float ang = 0;

    CTransform(const Vec2 &pos_in,const Vec2 &speed_in, float ang_in)
        : pos(pos_in), speed(speed_in), ang(ang_in)
    {
    }
};

class CLifespan: public Component
{
public:
    int remaining = 0;
    int total = 0;
    CLifespan(int rm, int tl)
        : remaining(rm), total(tl)
    {
    }
};
 
class CInput: public Component
{
public:
    CInput() {}
};

class CBoundingBox: public Component
{
public:
    CBoundingBox() {}
};

class CAnimation: public Component
{
public:
    CAnimation() {}
};

class CGravity: public Component
{
public:
    CGravity() {}
};

class CState: public Component
{
public:
    CState() {}
};
