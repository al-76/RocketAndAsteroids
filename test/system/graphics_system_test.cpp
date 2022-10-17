#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "sprite_component.h"
#include "graphics_system.h"
#include "world.h"

using ::testing::_;

class MockWorldGraphics {
public:
    template<typename T>
    using OnComponent = std::function<void(Entity&, T&)>;

    MOCK_METHOD(void, forEachSpriteComponent, (OnComponent<SpriteComponent> onComponent));

    template<typename T>
    void forEachComponent(OnComponent<T> onComponent) {
        forEachSpriteComponent(onComponent);
    }
};

TEST(GraphicsSystem, update) {
    // Arrange
    auto world = MockWorldGraphics();
    auto system = TGraphicsSystem<MockWorldGraphics>();
    EXPECT_CALL(world, forEachSpriteComponent(_));

    // Act
    system.update(world, 10.f);

    // Assert
}