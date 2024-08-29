#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Vec2.h"

class Animation
{
private:
    sf::Sprite sprite;
    size_t frame_count;
    size_t current_frame;
    size_t speed;
    Vec2 size = {1,1};
    std::string name = "none";

public:
    Animation();
    Animation(const std::string& nameVar, const sf::Texture& t);
    Animation(const std::string & nameVar,const sf::Texture& t, size_t frameCount, size_t speed_var);

    void update();
    bool hasEndend() const;
    const std::string & getName();
    const Vec2 getSize() const;
    sf::Sprite & getSprite();


};