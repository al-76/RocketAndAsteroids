#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "shape_component.h"
#include "collision_system.h"
#include "world.h"

using ::testing::_;

class MockWorldCollision {
public:
    using OnComponentShape = World::OnComponent<ShapeComponent>;

    MOCK_METHOD(void, forEachComponentShape, (OnComponentShape onComponent));

    template<typename ...Ts>
    void forEachComponent(World::OnComponent<Ts...> onComponent) {}

    template<>
    void forEachComponent<ShapeComponent>(OnComponentShape onComponent) {
        forEachComponentShape(onComponent);
    }
};

TEST(CollisionSystem, update) {
    // Arrange
    auto world = MockWorldCollision();
    auto system = TCollisionSystem<MockWorldCollision>();
    EXPECT_CALL(world, forEachComponentShape(_));

    // Act
    system.update(world, 10.f);

    // Assert
}