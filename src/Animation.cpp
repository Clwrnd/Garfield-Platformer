#include "Animation.h"

#include <cmath>

Animation::Animation() {};

Animation::Animation(const std::string &nameVar, const sf::Texture &t)
    : Animation(nameVar, t, 1, 0)
{
}

Animation::Animation(const std::string &nameVar, const sf::Texture &t, size_t frame_countVar, size_t speed_var)
    : name(nameVar), frame_count(frame_countVar), speed(speed_var), current_frame(0), sprite(t)
{
    size = Vec2((float)t.getSize().x / frame_count, (float)t.getSize().y);
    sprite.setOrigin(size.x / 2.0f, size.y / 2.0f);
    sprite.setTextureRect(sf::IntRect(std::floor(current_frame) * size.x, 0, size.x, size.y));
}

const std::string &Animation::getName()
{
    return name;
}

const Vec2 &Animation::getSize() const
{
    return size;
}

sf::Sprite &Animation::getSprite()
{
    return sprite;
}

bool Animation::hasEndend() const
{
    return frame_count - 1 == current_frame;
}

void Animation::update()
{
    relativGame_frame++;

    if (speed != 0)
    {
        current_frame = (relativGame_frame / speed) % frame_count;
    }

    sprite.setTextureRect(sf::IntRect(std::floor(current_frame) * size.x, 0, size.x, size.y));
}

void Animation::mmkNonRepeating()
{
    noRepeat = true;
}

bool Animation::isRepeating()
{
    return !noRepeat;
}
