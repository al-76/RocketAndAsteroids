#pragma once

#include "system.h"
#include "world.h"
#include "input_component.h"

template<typename T>
class TInputSystem final: public System<T> {
public:
    void update(T& world, float delta) override {
        world.template forEachComponent<InputComponent>([](Entity& entity, InputComponent& component) {
        });
    }
};

using InputSystem = TInputSystem<World>;