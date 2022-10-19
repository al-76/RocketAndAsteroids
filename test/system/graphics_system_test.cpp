#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "graphics_system.h"
#include "world.h"
#include "sprite_component.h"
#include "position_component.h"

using ::testing::_;

class MockWorldGraphics {
public:
    using OnComponentSprite = World::OnComponent<SpriteComponent>;
    using OnComponentPositionSprite = World::OnComponent<PositionComponent, SpriteComponent>;

    MOCK_METHOD(void, forEachComponentSprite, (OnComponentSprite onComponent));
    MOCK_METHOD(void, forEachComponentPositionSprite, (OnComponentPositionSprite onComponent));

    template<typename ...Ts>
    void forEachComponent(World::OnComponent<Ts...> onComponent) {}

    template<>
    void forEachComponent<SpriteComponent>(OnComponentSprite onComponent) {
        forEachComponentSprite(onComponent);
    }

    template<>
    void forEachComponent<PositionComponent, SpriteComponent>(OnComponentPositionSprite onComponent) {
        forEachComponentPositionSprite(onComponent);
    }
};

TEST(GraphicsSystem, load) {
    // Arrange
    auto world = MockWorldGraphics();
    auto system = TGraphicsSystem<MockWorldGraphics>();
    EXPECT_CALL(world, forEachComponentSprite(_));

    // Act
    system.load(world);

    // Assert
}

TEST(GraphicsSystem, update) {
    // Arrange
    auto world = MockWorldGraphics();
    auto system = TGraphicsSystem<MockWorldGraphics>();
    EXPECT_CALL(world, forEachComponentPositionSprite(_));

    // Act
    system.update(world, 10.f);

    // Assert
}