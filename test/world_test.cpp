#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "system/system.h"
#include "world/world.h"

using ::testing::Ref;

class MockSystem: public System<World> {
public:
    int tag;

    MockSystem(int tag = 0): tag(tag) {}

    MOCK_METHOD(void, update, (World& world, float delta), (override));
};

struct TestComponent { int value; };

TEST(World, addSystem) {
    // Arrange
    int testTag = 1000;
    auto world = World();

    // Act
    auto& system = world.addSystem<MockSystem>(testTag);

    // Assert
    EXPECT_EQ(system.tag, testTag);
}

TEST(World, update) {
    // Arrange
    float testDelta = 10.0f;
    auto world = World();
    auto& system = world.addSystem<MockSystem>();
    EXPECT_CALL(system, update(Ref(world), testDelta));

    // Act
    world.update(testDelta);

    // Assert
}

TEST(World, forEachComponent) {
    // Arrange
    auto world = World();
    auto& testEntity = world.createEntity();
    auto& testComponent = testEntity.addComponent<TestComponent>(10);
    bool called = false;

    // Act
    world.forEachComponent<TestComponent>([&](Entity& entity, TestComponent& component) {
        EXPECT_EQ(std::addressof(testEntity), std::addressof(entity));
        EXPECT_EQ(std::addressof(testComponent), std::addressof(component));
        called = true;
    });

    // Assert
    EXPECT_TRUE(called);
}

TEST(World, forEachComponentNotAdded) {
    // Arrange
    auto world = World();
    auto& testEntity = world.createEntity();
    bool called = false;

    // Act
    world.forEachComponent<TestComponent>([&](Entity& entity, TestComponent& component) {
        called = true;
    });

    // Assert
    EXPECT_FALSE(called);
}

