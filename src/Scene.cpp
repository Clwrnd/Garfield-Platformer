#include "Scene.h"

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