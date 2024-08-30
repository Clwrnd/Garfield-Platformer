#include "Entity.h"

const std::string &Entity::getTag() const
{
    return this->tag;
}

Entity::Entity(const size_t id_in, const std::string &tag_in)
    : id(id_in), tag(tag_in), components(ComponentTuple(CTransform(), CLifespan(), 
    CInput(), CBoundingBox(), CAnimation(), CGravity(), CState()))
{
}

bool Entity::isActive() const
{
    return active;
}

void Entity::destroy()
{
    active = false;
}

const size_t Entity::getId() const
{
    return this->id;
}
