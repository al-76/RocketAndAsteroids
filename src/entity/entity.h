#pragma once

#include <algorithm>
#include <typeindex>
#include <unordered_map>
#include <optional>
#include <memory>

#include "component_container.h"

class Entity;

using EntityPtr = std::unique_ptr<Entity>;
using BaseComponentContainerPtr = std::unique_ptr<BaseComponentContainer>;
using ComponentMap = std::unordered_map<std::type_index, BaseComponentContainerPtr>;

class Entity final {
public:
    Entity(ComponentMap&& components) {
        std::move(components.begin(), components.end(),
            std::inserter(this->components, this->components.begin()));
    }
    ~Entity() = default;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    Entity(const Entity&) = delete;
    const Entity& operator=(const Entity&) = delete;

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

class EntityBuilder final {
public:
    EntityPtr build() {
        return std::make_unique<Entity>(std::move(components));
    }

    EntityBuilder() = default;
    ~EntityBuilder() = default;

    EntityBuilder(EntityBuilder&&) = default;
    EntityBuilder& operator=(EntityBuilder&&) = default;

    EntityBuilder(const EntityBuilder&) = delete;
    const EntityBuilder& operator=(const EntityBuilder&) = delete;

    template<typename T, typename... Args>
    EntityBuilder& addComponent(Args&&... args) {
        components[std::type_index(typeid(T))] = std::make_unique<ComponentContainer<T>>(T { std::forward<Args>(args)... }); // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
        return *this;
    }

private:
    ComponentMap components;
};