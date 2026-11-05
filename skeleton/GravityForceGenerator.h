#pragma once
#include "ForceGenerator.h"
class GravityForceGenerator : public ForceGenerator
{
public:
    GravityForceGenerator(const Vector3D& g) noexcept;
    void updateForce(Particle* p) noexcept override;

private:
    Vector3D gravity;
};

