#pragma once
#include "ForceGenerator.h"
class WindForceGenerator : public ForceGenerator
{
public:
    WindForceGenerator(const Vector3D& windV, float _k1, float _k2, const Vector3D& center, float radius) noexcept;
    void updateForce(Particle* p) override;

protected:
    Vector3D windVel;
    float k1;
    float k2;
    Vector3D influenceCenter;
    float influenceRadius;
    float influenceRadiusSq;
};

