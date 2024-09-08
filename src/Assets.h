#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Animation.h"

class Assets
{
private:
    std::map<std::string, sf::Font> a_fonts;
    std::map<std::string, sf::Texture> a_textures;
    std::map<std::string, Animation> a_animations;
    std::map<std::string, sf::SoundBuffer> a_soundsBuffer;


public:
    Assets();

    void addTexture(std::string &name, std::string &path);
    void addAnimation(std::string &name, Animation &animation);
    void addSoundBuffer(std::string &name, std::string &path);
    void addFont(const std::string &name, const std::string &path);

    const sf::Texture &getTexture(const std::string &name) const;
    const Animation &getAnimation(const std::string &name) const;
    const sf::SoundBuffer &getSoundBuffer(const std::string &name) const;
    const sf::Font &getFont(const std::string &name) const;
};