#pragma once

#include "system.h"
#include "world/world.h"
#include "component/rectangle_component.h"

template<typename T>
class TGraphicsSystem final: public System<T> {
public:
    void update(T& world, float delta) override {
        world.template forEachComponent<RectangleComponent>([](Entity& entity, RectangleComponent& component) {
        });
    }
};

using GraphicsSystem = TGraphicsSystem<World>;