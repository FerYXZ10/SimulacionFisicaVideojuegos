#pragma once
#include "Particle.h"
class ForceGenerator
{
public:
    virtual ~ForceGenerator() = default;
    virtual void tick(double dt) noexcept {}
    virtual void updateForce(Particle* p) = 0;
};

