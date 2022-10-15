#pragma once

#include <functional>

struct InputComponent final {
    enum Key {
        W,
        A,
        S,
        D
    };

    std::function<void(Key)> onKeyPressed;
};