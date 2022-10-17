#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>

#include "entity.h"
#include "system.h"

class World;

using SystemPtr = std::unique_ptr<System<World>>;

class World {
public:
    World(std::vector<SystemPtr>&& systems,
          std::vector<EntityPtr>&& entities) {
        std::move(systems.begin(), systems.end(),
            std::back_inserter(this->systems));
        std::move(entities.begin(), entities.end(),
            std::back_inserter(this->entities));

        for (const auto& system: this->systems) {
            system->load(*this);
        }
    }
    virtual ~World() = default;

    World(World&&) = default;
    World& operator=(World&&) = default;

    World(const World&) = delete;
    const World& operator=(const World&) = delete;

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

class WorldBuilder {
public:
    World build() {
        return { std::move(systems), std::move(entities) };
    }

    WorldBuilder() = default;
    virtual ~WorldBuilder() = default;

    WorldBuilder(WorldBuilder&&) = default;
    WorldBuilder& operator=(WorldBuilder&&) = default;

    WorldBuilder(const WorldBuilder&) = delete;
    const WorldBuilder& operator=(const WorldBuilder&) = delete;

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
    std::vector<SystemPtr> systems; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
    std::vector<EntityPtr> entities; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)
};