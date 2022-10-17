#pragma once

template<typename T>
class System {
public:
    System() = default;
    virtual ~System() = default;

    System(System&&) = default;
    System& operator=(System&&) = default;

    System(const System&) = delete;
    const System& operator=(const System&) = delete;

    virtual void load(T& world) {}
    virtual void update(T& world, float delta) = 0;
};