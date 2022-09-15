#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "component/rectangle_component.h"
#include "system/graphics_system.h"
#include "world/world.h"

using ::testing::_;

class MockWorldGraphics {
public:
    template<typename T>
    using OnComponent = std::function<void(Entity&, T&)>;

    MOCK_METHOD(void, forEachComponentRectangle, (OnComponent<RectangleComponent> onComponent));

    template<typename T>
    void forEachComponent(OnComponent<T> onComponent) {
        forEachComponentRectangle(onComponent);
    }
};

TEST(GraphicsSystem, update) {
    // Arrange
    auto world = MockWorldGraphics();
    auto system = TGraphicsSystem<MockWorldGraphics>();
    EXPECT_CALL(world, forEachComponentRectangle(_));

    // Act
    system.update(world, 10.f);

    // Assert
}