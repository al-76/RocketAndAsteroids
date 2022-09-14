// #include <iostream>

// #include <SDL.h>

#include "world/world.h"
#include "system/collision_system.h"
#include "system/game_logic_system.h"
#include "system/graphics_system.h"
#include "system/input_system.h"
#include "component/actor_component.h"
#include "component/input_component.h"
#include "component/particle_component.h"
#include "component/rectangle_component.h"
#include "component/shape_component.h"

int main() {
    auto world = World();

    world.addSystem<CollisionSystem>();
    world.addSystem<GameLogicSystem>();
    world.addSystem<GraphicsSystem>();
    world.addSystem<InputSystem>();

    // rocket
    auto& entity = world.createEntity();
    entity.addComponent<ActorComponent>();
    entity.addComponent<InputComponent>();
    entity.addComponent<RectangleComponent>(0.f, 0.f, 30.f, 30.f);
    entity.addComponent<ShapeComponent>(30);

    // asteroids
    for (int i = 0; i < 30; ++i) {
        auto& entity = world.createEntity();
        entity.addComponent<ParticleComponent>();
        entity.addComponent<RectangleComponent>(0.f, 0.f, 5.f, 5.f);
        entity.addComponent<ShapeComponent>(5);
    }

    world.update(10.f);

    return 0;
}