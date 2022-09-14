#pragma once

#include "system.h"
#include "world/world.h"
#include "component/actor_component.h"
#include "component/particle_component.h"

template<typename T>
class TGameLogicSystem: public System<T> {
public:
    virtual void update(T& world, float delta) override {
        world.template forEachComponent<ActorComponent>([](Entity& entity, ActorComponent& component) {
        });

        world.template forEachComponent<ParticleComponent>([](Entity& entity, ParticleComponent& component) {
        });
    }
};

using GameLogicSystem = TGameLogicSystem<World>;