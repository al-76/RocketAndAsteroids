#pragma once

#include "system.h"
#include "world/world.h"
#include "component/input_component.h"

template<typename T>
class TInputSystem: public System<T> {
public:
    virtual void update(T& world, float delta) override {
        world.template forEachComponent<InputComponent>([](Entity& entity, InputComponent& component) {
        });
    }
};

using InputSystem = TInputSystem<World>;