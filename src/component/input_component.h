#pragma once

#include <functional>

struct InputComponent {
    enum Key {
        W,
        A,
        S,
        D
    };

    std::function<void(Key)> onKeyPressed;
};