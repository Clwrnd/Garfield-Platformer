#pragma once

#include <string>

class Action
{
private:
    std::string name = "NONE";
    std::string type = "NONE";
    unsigned long frame = 0;

public:
    Action();
    Action(const std::string &nameVar, const std::string &typeVar);
    Action(const std::string &nameVar, const std::string &typeVar, unsigned long f);

    const std::string &getName() const;
    const std::string &getType() const;
    const unsigned long &getFrame() const;
    std::string toString() const;
};