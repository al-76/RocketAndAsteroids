#include "world/world.h"
#include "system/systems.h"
#include "component/components.h"

int main() {
    // world
    auto worldBuilder = WorldBuilder();
    worldBuilder
    .addSystem<CollisionSystem>()
    .addSystem<GameLogicSystem>()
    .addSystem<GraphicsSystem>()
    .addSystem<InputSystem>();

    // rocket
    auto rocketBuilder = EntityBuilder();
    rocketBuilder
    .addComponent<ActorComponent>()
    .addComponent<InputComponent>()
    .addComponent<RectangleComponent>(0.f, 0.f, 30.f, 30.f)
    .addComponent<ShapeComponent>(30);
    worldBuilder.addEntity(rocketBuilder.build());

    // asteroids
    for (int i = 0; i < 30; ++i) {
        auto asteroidBuilder = EntityBuilder();
        asteroidBuilder
        .addComponent<ParticleComponent>()
        .addComponent<RectangleComponent>(0.f, 0.f, 5.f, 5.f)
        .addComponent<ShapeComponent>(5);
        worldBuilder.addEntity(asteroidBuilder.build());
    }

    worldBuilder
    .build()
    .update(10.f);

    return 0;
}