#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>

#include "actor_component.h"
#include "particle_component.h"
#include "game_logic_system.h"
#include "world.h"

using ::testing::_;

class MockWorldLogic {
public:
    using OnComponentActor = World::OnComponent<ActorComponent>;
    using OnComponentParticle = World::OnComponent<ParticleComponent>;

    MOCK_METHOD(void, forEachComponentActor, (OnComponentActor onComponent));
    MOCK_METHOD(void, forEachComponentParticle, (OnComponentParticle onComponent));

    template<typename ...Ts>
    void forEachComponent(World::OnComponent<Ts...> onComponent) {}

    template<>
    void forEachComponent<ActorComponent>(OnComponentActor onComponent) {
        forEachComponentActor(onComponent);
    }

    template<>
    void forEachComponent<ParticleComponent>(OnComponentParticle onComponent) {
        forEachComponentParticle(onComponent);
    }
};

TEST(GameLogicSystem, update) {
    // Arrange
    auto world = MockWorldLogic();
    auto system = TGameLogicSystem<MockWorldLogic>();
    EXPECT_CALL(world, forEachComponentActor(_));
    EXPECT_CALL(world, forEachComponentParticle(_));

    // Act
    system.update(world, 10.f);

    // Assert
}