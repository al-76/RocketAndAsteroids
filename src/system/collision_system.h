#pragma once

#include "system.h"
#include "world/world.h"
#include "component/shape_component.h"

template<typename T>
class TCollisionSystem: public System<T> {
public:
    virtual void update(T& world, float delta) override {
        world.template forEachComponent<ShapeComponent>([](Entity& entity, ShapeComponent& component) {
        });
    }
};

using CollisionSystem = TCollisionSystem<World>;