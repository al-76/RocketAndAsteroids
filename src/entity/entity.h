#pragma once

#include <set>
#include <typeindex>
#include <unordered_map>
#include <optional>
#include <memory>

#include "component/component_container.h"
#include "util/noncopyable.h"

class Entity: public NonCopyable {
public:
    template<typename T, typename... Args>
    T& addComponent(Args&&... args) {
        auto key = std::type_index(typeid(T));
        components.emplace(key,
            std::make_unique<ComponentContainer<T>>(T { std::forward<Args>(args)... }));
        
        auto item = getComponentContainer<T>(components[key].get());
        return item->get();
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
    using BaseComponentContainerPtr = std::unique_ptr<BaseComponentContainer>;

    std::unordered_map<std::type_index, BaseComponentContainerPtr> components;

    template<typename T>
    ComponentContainer<T>* getComponentContainer(BaseComponentContainer* baseContainer) {
        return static_cast<ComponentContainer<T>*>(baseContainer);
    }
};