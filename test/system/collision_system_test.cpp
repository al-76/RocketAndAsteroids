#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "shape_component.h"
#include "collision_system.h"
#include "world.h"

using ::testing::_;

class MockWorldCollision {
public:
    template<typename T>
    using OnComponent = std::function<void(Entity&, T&)>;

    MOCK_METHOD(void, forEachComponentShape, (OnComponent<ShapeComponent> onComponent));

    template<typename T>
    void forEachComponent(OnComponent<T> onComponent) {
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