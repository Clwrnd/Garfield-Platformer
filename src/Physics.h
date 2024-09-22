#pragma once

#include <memory>

#include "Entity.h"
#include "Vec2.h"

class Physics
{
    Vec2 getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
    Vec2 getPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);
};