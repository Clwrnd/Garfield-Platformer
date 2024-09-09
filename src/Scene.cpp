#include "Scene.h"

#include "GameEngine.h"

Scene::Scene() {}

Scene::Scene(GameEngine *g)
    : game_engine(g)
{
}
const ActionMap &Scene::getActionMap() const
{
    return actionMap;
}

bool Scene::getHasEnded() const
{
    return hasEnded;
}

void Scene::registerAction(int inputKey, const std::string &actionName)
{
    actionMap[inputKey] = actionName;
}

void Scene::doAction(const Action &action)
{
    sDoAction(action);
}

void Scene::drawLine(const Vec2 &p1, const Vec2 &p2)
{
    sf::RectangleShape rect;
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(sf::Vector2f(p1.x,p1.y));
    rect.setSize(sf::Vector2f(p2.x,p2.y));
    game_engine->getWindow().draw(rect); 
}
