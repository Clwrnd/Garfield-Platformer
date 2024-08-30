#include "Action.h"

Action::Action() {};

Action::Action(const std::string &nameVar, const std::string &typeVar)
    : name(nameVar), type(typeVar)
{
}

const std::string &Action::getName() const
{
    return name;
}

const std::string &Action::getType() const
{
    return type;
}

std::string Action::toString() const
{
    return "Nature de l'action: " + name;
}