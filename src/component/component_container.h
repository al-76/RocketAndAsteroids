#pragma once

class BaseComponentContainer {
};

template<typename T>
class ComponentContainer: public BaseComponentContainer {
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