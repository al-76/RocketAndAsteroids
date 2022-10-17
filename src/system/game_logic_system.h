#pragma once

#include "system.h"
#include "world.h"
#include "actor_component.h"
#include "particle_component.h"

template<typename T>
class TGameLogicSystem final: public System<T> {
public:
    void update(T& world, float delta) override {
        world.template forEachComponent<ActorComponent>([](Entity& entity, ActorComponent& component) {
        });

        world.template forEachComponent<ParticleComponent>([](Entity& entity, ParticleComponent& component) {
        });
    }
};

using GameLogicSystem = TGameLogicSystem<World>;