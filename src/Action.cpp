#include "Action.h"

Action::Action() {};

Action::Action(const std::string &nameVar, const std::string &typeVar)
    : name(nameVar), type(typeVar)
{
}

Action::Action(const std::string &nameVar, const std::string &typeVar, unsigned long f)
    : name(nameVar), type(typeVar), frame(f)
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

const unsigned long &Action::getFrame() const
{
    return frame;
}

std::string Action::toString() const
{
    return "Nature de l'action: " + name;
}