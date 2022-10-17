#pragma once

#include <iostream>

#include "system.h"
#include "world.h"
#include "sprite_component.h"

template<typename T>
class TGraphicsSystem final: public System<T> {
public:
    void load(T& world) override {
        world.template forEachComponent<SpriteComponent>([](Entity& entity, SpriteComponent& component) {
            if (!component.texture.loadFromFile(component.fileName)) {
                return;
            }
            component.sprite.setTexture(component.texture);
        });
    }

    void update(T& world, float delta) override {
        world.template forEachComponent<SpriteComponent>([](Entity& entity, SpriteComponent& component) {
        });
    }
};

using GraphicsSystem = TGraphicsSystem<World>;