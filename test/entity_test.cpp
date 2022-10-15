#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "entity/entity.h"

struct TestComponent final { int value; };

TEST(Entity, getComponent) {
    // Arrange
    int testValue = 1000;
    auto entity = EntityBuilder()
    .addComponent<TestComponent>(testValue)
    .build();

    // Act
    auto component = entity->getComponent<TestComponent>();

    // Assert
    EXPECT_EQ(component->value, testValue);
}