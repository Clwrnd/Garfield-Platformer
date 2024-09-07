#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Vec2.h"

class Animation
{
private:
    sf::Sprite sprite;
    std::string name = "none";
    Vec2 size = {1, 1};
    size_t frame_count;
    size_t current_frame;
    size_t speed;
    size_t relativGame_frame = 0;

public:
    Animation();
    Animation(const std::string &nameVar, const sf::Texture &t);
    Animation(const std::string &nameVar, const sf::Texture &t, size_t frame_countVar, size_t speed_var);

    const std::string &getName();
    const Vec2 &getSize() const;
    sf::Sprite &getSprite();
    bool hasEndend() const;
    void update();
};