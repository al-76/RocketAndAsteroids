#include "ecs.h"

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
    .addComponent<SpriteComponent>("res/ship.png") // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    .addComponent<ShapeComponent>(30); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
    worldBuilder.addEntity(rocketBuilder.build());

    // asteroids
    for (int i = 0; i < 30; ++i) { // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        auto asteroidBuilder = EntityBuilder();
        asteroidBuilder
        .addComponent<ParticleComponent>()
        .addComponent<SpriteComponent>("res/asteroid.png") // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        .addComponent<ShapeComponent>(5); // NOLINT(cppcoreguidelines-avoid-magic-numbers)
        worldBuilder.addEntity(asteroidBuilder.build());
    }

    worldBuilder
    .build()
    .update(10.f); // NOLINT(cppcoreguidelines-avoid-magic-numbers)

    return 0;
}