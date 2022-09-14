#include "world/world.h"
#include "system/systems.h"
#include "component/components.h"

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