#pragma once

#include "Component.h"

#include <string>
#include <tuple>

typedef std::tuple<
    CTransform,
    CLifespan,
    CInput,
    CBoundingBox,
    CAnimation,
    CGravity,
    CState
> ComponentTuple;

class Entity
{
    friend class EntityManager;

private:
    bool active = true;
    size_t id = 0;
    std::string tag = "default";
    ComponentTuple components;

    Entity(const size_t id_in, const std::string &tag_in);

public:
    

    bool isActive() const;
    const size_t getId() const;
    const std::string &getTag() const;
    void destroy();

    template <typename T> bool hasComponent() const
    {
        return getComponent<T>().has();
    }

    template <typename T,typename ... TArgs> T& addComponent(TArgs&&... mArgs)
    {
        auto & components = getComponent<T>();
        components = T(std::forward<TArgs>(mArgs)...);
        components.has = true;
        return components;
    }

    template <typename T> T& getComponent()
    {
        return std::get<T>(components);
    }

    template <typename T> void removeComponent()
    {
        getComponent<T>()=T();
    }

};
