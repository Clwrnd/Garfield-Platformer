#include "Physics.h"

#include <cmath>

Vec2 Physics::getOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    Vec2 delta{std::abs(a->getComponent<CTransform>().pos.x - b->getComponent<CTransform>().pos.x),
               std::abs(a->getComponent<CTransform>().pos.y - b->getComponent<CTransform>().pos.y)};

    float ox = (a->getComponent<CBoundingBox>().width / 2) + (b->getComponent<CBoundingBox>().width / 2) - delta.x;
    float oy = (a->getComponent<CBoundingBox>().height / 2) + (b->getComponent<CBoundingBox>().height / 2) - delta.y;

    return Vec2(ox, oy);
}

Vec2 Physics::getPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
    Vec2 delta{std::abs(a->getComponent<CTransform>().previousPos.x - b->getComponent<CTransform>().previousPos.x),
               std::abs(a->getComponent<CTransform>().previousPos.y - b->getComponent<CTransform>().previousPos.y)};

    float ox = (a->getComponent<CBoundingBox>().width / 2) + (b->getComponent<CBoundingBox>().width / 2) - delta.x;
    float oy = (a->getComponent<CBoundingBox>().height / 2) + (b->getComponent<CBoundingBox>().height / 2) - delta.y;

    return Vec2(ox, oy);
}
