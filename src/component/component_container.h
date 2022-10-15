#pragma once

class BaseComponentContainer {
};

template<typename T>
class ComponentContainer final : public BaseComponentContainer {
public:
    ComponentContainer(T&& component):
    component(std::forward<T>(component)) {
    }

    T& get() {
        return component;
    }

private:
    T component;
};