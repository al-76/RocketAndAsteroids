#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "system.h"
#include "world.h"

using ::testing::Ref;
using ::testing::_;

class MockSystem: public System<World> {
public:
    MOCK_METHOD(void, load, (World& world), (override));
    MOCK_METHOD(void, update, (World& world, float delta), (override));
};

class MockWorldBuilder: public WorldBuilder {
public:
    MockSystem& lastSystem() {
        return *dynamic_cast<MockSystem *>(systems.back().get());
    }
};

struct TestComponent { int value; };

TEST(World, load) {
    // Arrange
    auto worldBuilder = MockWorldBuilder();
    worldBuilder.addSystem<MockSystem>();
    EXPECT_CALL(worldBuilder.lastSystem(), load(_));

    // Act
    auto world = worldBuilder.build();

    // Assert
}

TEST(World, update) {
    // Arrange
    auto worldBuilder = MockWorldBuilder();
    worldBuilder.addSystem<MockSystem>();
    EXPECT_CALL(worldBuilder.lastSystem(), update(_, 10.f));
    auto world = worldBuilder.build();

    // Act
    world.update(10.f);

    // Assert
}

TEST(World, forEachComponent) {
    // Arrange
    auto entityBuilder = EntityBuilder();
    entityBuilder.addComponent<TestComponent>(10);
    auto world = WorldBuilder()
    .addEntity(entityBuilder.build())
    .build();
    bool called = false;

    // // Act
    world.forEachComponent<TestComponent>([&](Entity& entity, TestComponent& component) {
        called = true;
    });

    // Assert
    EXPECT_TRUE(called);
}

TEST(World, forEachComponentNotAdded) {
    // Arrange
    auto world = WorldBuilder()
    .addEntity(EntityBuilder().build())
    .build();
    bool called = false;

    // Act
    world.forEachComponent<TestComponent>([&](Entity& entity, TestComponent& component) {
        called = true;
    });

    // Assert
    EXPECT_FALSE(called);
}

