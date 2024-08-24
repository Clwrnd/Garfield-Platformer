#include "GameEngine.h"
#include <string>

void GameEngine::init(const std::string &config)
{
    window.create(sf::VideoMode({1400,800}),"Assignement 3");
    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
}

        window.clear();
        window.display();
    }
}

GameEngine::GameEngine(const std::string &config)
{
    init(config);
}