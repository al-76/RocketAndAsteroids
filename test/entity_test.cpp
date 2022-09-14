#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "entity/entity.h"

struct TestComponent { int value; };

TEST(Entity, addComponent) {
    // Arrange
    int testValue = 1000;
    auto entity = Entity();

    // Act
    auto& component = entity.addComponent<TestComponent>(testValue);

    // Assert
    EXPECT_EQ(component.value, testValue);
}

TEST(Entity, getComponent) {
    // Arrange
    auto entity = Entity();
    auto& addedComponent = entity.addComponent<TestComponent>(1000);

    // Act
    auto component = entity.getComponent<TestComponent>();

    // Assert
    EXPECT_EQ(std::addressof(*component), std::addressof(addedComponent));
}