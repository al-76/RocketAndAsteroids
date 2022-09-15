#pragma once

#include "util/noncopyable.h"

template<typename T>
class System: public NonCopyable {
public:
    virtual void update(T& world, float delta) = 0;

    virtual ~System() = default;
};