#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "input_component.h"
#include "input_system.h"
#include "world.h"

using ::testing::_;

class MockWorldInput {
public:
    using OnComponentInput = World::OnComponent<InputComponent>;

    MOCK_METHOD(void, forEachComponentInput, (OnComponentInput onComponent));

    template<typename ...Ts>
    void forEachComponent(World::OnComponent<Ts...> onComponent) {}

    template<>
    void forEachComponent<InputComponent>(OnComponentInput onComponent) {
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