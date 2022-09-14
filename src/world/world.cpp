#include "world.h"

Entity& World::createEntity() {
    entities.push_back(std::make_unique<Entity>());
    return *(entities.back().get());
}

void World::update(float delta) {
    for(const auto& system: systems) {
        system->update(*this, delta);
    }
}