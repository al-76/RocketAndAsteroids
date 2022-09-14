#pragma once

// template<typename World>
// class AnyWorld;
// class World;

template<typename T>
class System {
public:
    virtual void update(T& world, float delta) = 0;

    virtual ~System() = default;
};