#pragma once
#include <string>

class Action
{
private: 
    std::string name = "NONE";
    std::string type = "NONE";
 
public:
    Action();
    Action(const std::string & nameVar, const std::string & typeVar);

    const std::string & getName() const;
    const std::string & getType() const;
    std::string toString() const;
};