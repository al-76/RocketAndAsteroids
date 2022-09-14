#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>

#include "entity/entity.h"
#include "system/system.h"
#include "util/noncopyable.h"

class World: public NonCopyable {
public:
    template<typename T, typename... Args>
    T& addSystem(Args&&... args) {
        systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return static_cast<T&>(*systems.back().get());
    }

    template<typename T>
    void forEachComponent(std::function<void(Entity&, T&)> onComponent) {
        for (auto& entity: entities) {
            auto ptrEntity = entity.get();
            T* component = ptrEntity->getComponent<T>();
            if (component != nullptr) {
                onComponent(*ptrEntity, *component);
            }
        }
    }

    Entity& createEntity();
    void update(float delta);

private:
    std::vector<std::unique_ptr<System<World>>> systems;
    std::vector<std::unique_ptr<Entity>> entities;
};

// template<typename World>
// class AnyWorld: public NonCopyable {
// public:
//     AnyWorld(World* world): world(world) {}

//     template<typename T, typename... Args>
//     T& addSystem(Args&&... args) {
//         return world.addSystem(std::forward<Args>(args)...);
//     }

//     template<typename T>
//     void forEachComponent(std::function<void(Entity&, T&)> onComponent) {
//         world.forEachComponent(onComponent);
//     }

//     Entity& createEntity() {
//         return world.createEntity();
//     }

//     void update(float delta) {
//         world.update(delta);
//     }

// private:
//     World* world;
// };