#include "Assets.h"

Assets::Assets() {};

void Assets::addTexture(std::string & name,std::string & path)
{
    a_textures[name]= sf::Texture();
    a_textures[name].loadFromFile(path);
}

void Assets::addAnimation(std::string & name,Animation & animation)
{
    a_animations[name] = animation;

}

void Assets::addSound(std::string & name,std::string & path)
{
    sf::SoundBuffer sound_buffer;
    sound_buffer.loadFromFile(path);
    a_sounds[name]= sf::Sound(sound_buffer);
}
   
void Assets::addFont(const std::string & name,const std::string & path)
{
    a_fonts[name]= sf::Font();
    a_fonts[name].loadFromFile(path);
}

const sf::Texture & Assets::getTexture(std::string & name) const
{
    return a_textures.at(name);
}
    
const Animation & Assets::getAnimation(std::string & name) const
{
    return a_animations.at(name);
}

const sf::Sound & Assets::getSound(std::string & name) const
{
    return a_sounds.at(name);
}

const sf::Font & Assets::getFont(const std::string & name) const  
{
    return a_fonts.at(name);
}