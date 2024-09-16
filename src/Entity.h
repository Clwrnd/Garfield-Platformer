#pragma once

#include <string>
#include <tuple>

#include "Component.h"

typedef std::tuple<
    CTransform,
    CLifespan,
    CInput,
    CBoundingBox,
    CAnimation,
    CGravity,
    CState>
    ComponentTuple;

class Entity
{
    friend class EntityManager;

private:
    std::string tag = "default";
    ComponentTuple components;
    size_t id = 0;
    bool active = true;

    Entity(const size_t id_in, const std::string &tag_in);

public:
    const size_t getId() const;
    const std::string &getTag() const;
    void destroy();
    bool isActive() const;

    template <typename T>
    bool hasComponent()
    {
        return getComponent<T>().has;
    }

    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&...mArgs)
    {
        auto &components = getComponent<T>();
        components = T(std::forward<TArgs>(mArgs)...);
        components.has = true;
        return components;
    }

    template <typename T>
    T &getComponent()
    {
        return std::get<T>(components);
    }

    template <typename T>
    void removeComponent()
    {
        getComponent<T>() = T();
    }
};
