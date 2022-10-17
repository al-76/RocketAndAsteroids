#pragma once

#include "system.h"
#include "world.h"
#include "shape_component.h"

template<typename T>
class TCollisionSystem final: public System<T> {
public:
    void update(T& world, float delta) override {
        world.template forEachComponent<ShapeComponent>([](Entity& entity, ShapeComponent& component) {
        });
    }
};

using CollisionSystem = TCollisionSystem<World>;