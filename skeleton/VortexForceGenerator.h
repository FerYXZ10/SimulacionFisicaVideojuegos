#pragma once
#include "WindForceGenerator.h"
class VortexForceGenerator : public WindForceGenerator
{
public:
    VortexForceGenerator(const Vector3D& cent, float radius, float str, float k1, float k2) noexcept;
    void updateForce(Particle* p, double t) override;

private:
    Vector3D computeWindVel(const Vector3D& position) const noexcept;

    float strength;
};

