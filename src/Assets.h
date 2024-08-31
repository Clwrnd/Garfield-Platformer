#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Animation.h"

class Assets
{
private:
    std::map<std::string,sf::Font> a_fonts;
    std::map<std::string,sf::Texture> a_textures;
    std::map<std::string,Animation> a_animations;
    std::map<std::string,sf::Sound> a_sounds;
    
public:
    Assets();

    void addTexture(std::string & name,std::string & path);
    void addAnimation(std::string & name,Animation & animation);
    void addSound(std::string & name ,std::string &path);    
    void addFont(const std::string & name,const std::string & path);

    sf::Texture & getTexture(std::string & name);
    Animation & getAnimation(std::string & name);
    sf::Sound & getSound(std::string & name);
    const sf::Font & getFont(const std::string & name) const;
};