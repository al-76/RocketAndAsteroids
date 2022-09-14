#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>

#include "component/actor_component.h"
#include "component/particle_component.h"
#include "system/game_logic_system.h"
#include "world/world.h"

using ::testing::_;

class MockWorldLogic {
public:
    template<typename T>
    using OnComponent = std::function<void(Entity&, T&)>;
    using OnComponentActor = OnComponent<ActorComponent>;
    using OnComponentParticle = OnComponent<ParticleComponent>;

    MOCK_METHOD(void, forEachComponentActor, (OnComponent<ActorComponent> onComponent));
    MOCK_METHOD(void, forEachComponentParticle, (OnComponent<ParticleComponent> onComponent));

    template<typename T>
    void forEachComponent(OnComponent<T> onComponent) {}

    template<>
    void forEachComponent(OnComponent<ActorComponent> onComponent) {
        forEachComponentActor(onComponent);
    }

    template<>
    void forEachComponent(OnComponent<ParticleComponent> onComponent) {
        forEachComponentParticle(onComponent);
    }
};

TEST(GameLogicSystem, update) {
    // Arrange
    auto entity = Entity();
    auto world = MockWorldLogic();
    auto system = TGameLogicSystem<MockWorldLogic>();
    EXPECT_CALL(world, forEachComponentActor(_));
    EXPECT_CALL(world, forEachComponentParticle(_));

    // Act
    system.update(world, 10.f);

    // Assert
}