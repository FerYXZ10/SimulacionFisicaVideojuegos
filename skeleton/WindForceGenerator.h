#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{
public:
    WindForceGenerator(const Vector3D& windV, float _k1, float _k2) noexcept;
    void updateForce(Particle* p, double t) noexcept override;

protected:
    Vector3D windVel;
    float k1;
    float k2;
};

