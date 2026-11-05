#pragma once
#include "ForceGenerator.h"
#include <cmath>
class ExplosionForceGenerator : public ForceGenerator
{
public:
    ExplosionForceGenerator(const Vector3D& center, float rad, float _k, float tau) noexcept;
    void tick(double dt) noexcept override;
    bool isFinished() const noexcept;
    void updateForce(Particle* p) override;

private:
	Vector3D computeExplosionForce(const Vector3D& position, double elapsed) const noexcept;

    Vector3D center;
    float radius;
    float k;
    float tau;
    float radiusSq;
    float elapsedTime = 0.0f;
};

