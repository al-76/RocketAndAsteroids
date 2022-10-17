#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "input_component.h"
#include "input_system.h"
#include "world.h"

using ::testing::_;

class MockWorldInput {
public:
    template<typename T>
    using OnComponent = std::function<void(Entity&, T&)>;

    MOCK_METHOD(void, forEachComponentInput, (OnComponent<InputComponent> onComponent));

    template<typename T>
    void forEachComponent(OnComponent<T> onComponent) {
        forEachComponentInput(onComponent);
    }
};

TEST(InputSystem, update) {
    // Arrange
    auto world = MockWorldInput();
    auto system = TInputSystem<MockWorldInput>();
    EXPECT_CALL(world, forEachComponentInput(_));

    // Act
    system.update(world, 10.f);

    // Assert
}