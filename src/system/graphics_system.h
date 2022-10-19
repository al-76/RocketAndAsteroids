#pragma once

#include "system.h"
#include "world.h"
#include "sprite_component.h"
#include "position_component.h"

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
        world.template forEachComponent<PositionComponent, SpriteComponent>([](Entity& entity,
            PositionComponent& positionComponent,
            SpriteComponent& spriteComponent) {
            spriteComponent.sprite.setPosition(positionComponent.x, positionComponent.y);
        });
    }
};

using GraphicsSystem = TGraphicsSystem<World>;