#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>

#include "entity/entity.h"
#include "system/system.h"
#include "util/noncopyable.h"

class World;

using SystemPtr = std::unique_ptr<System<World>>;

class World: public NonCopyable {
public:
    World(std::vector<SystemPtr>&& systems,
          std::vector<EntityPtr>&& entities) {
        std::move(systems.begin(), systems.end(),
            std::back_inserter(this->systems));
        std::move(entities.begin(), entities.end(),
            std::back_inserter(this->entities));
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

    void update(float delta) {
        for(const auto& system: systems) {
            system->update(*this, delta);
        }
    }

private:
    std::vector<SystemPtr> systems;
    std::vector<EntityPtr> entities;
};

class WorldBuilder: public NonCopyable {
public:
    World build() {
        return World(std::move(systems),
            std::move(entities));
    }

    template<typename T, typename... Args>
    WorldBuilder& addSystem(Args&&... args) {
        systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *this;
    }

    WorldBuilder& addEntity(EntityPtr&& entity) {
        entities.push_back(std::forward<EntityPtr>(entity));
        return *this;
    }

protected:
    std::vector<SystemPtr> systems;
    std::vector<EntityPtr> entities;
};