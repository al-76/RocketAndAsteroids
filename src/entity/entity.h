#pragma once

#include <algorithm>
#include <typeindex>
#include <unordered_map>
#include <optional>
#include <memory>

#include "component/component_container.h"
#include "util/noncopyable.h"

class Entity;

using EntityPtr = std::unique_ptr<Entity>;
using BaseComponentContainerPtr = std::unique_ptr<BaseComponentContainer>;
using ComponentMap = std::unordered_map<std::type_index, BaseComponentContainerPtr>;

class Entity: public NonCopyable {
public:
    Entity(ComponentMap&& components) {
        std::move(components.begin(), components.end(),
            std::inserter(this->components, this->components.begin()));
    }

    template<typename T>
    T* getComponent() {
        auto key = std::type_index(typeid(T));
        auto container = components.find(key);
        if (container == components.end()) {
            return nullptr;
        }

        auto item = getComponentContainer<T>(container->second.get());
        return &item->get();
    }

private:
    ComponentMap components;

    template<typename T>
    ComponentContainer<T>* getComponentContainer(BaseComponentContainer* baseContainer) {
        return static_cast<ComponentContainer<T>*>(baseContainer);
    }
};

class EntityBuilder: public NonCopyable {
public:
    EntityPtr build() {
        return std::make_unique<Entity>(std::move(components));
    }

    template<typename T, typename... Args>
    EntityBuilder& addComponent(Args&&... args) {
        components[std::type_index(typeid(T))] = std::make_unique<ComponentContainer<T>>(T { std::forward<Args>(args)... });
        return *this;
    }

private:
    ComponentMap components;
};