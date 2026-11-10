#pragma once
#include "ForceGenerator.h"
#include "Particle.h"
#include <cmath>
#include <algorithm>
class SpringForceGenerator : public ForceGenerator
{
public:
    SpringForceGenerator(float _k, float resting_length, Particle* p, float dampingRat = 0.05f) noexcept;
    virtual ~SpringForceGenerator() = default;

    virtual void updateForce(Particle* p) override;

    float getK() const noexcept;
    void setK(float _k) noexcept;

    float getDampingRatio() const noexcept;
	void setDampingRatio(float ratio) noexcept;

protected:
    float k;
    float restingLength;
    Particle* other;
    float dampingRatio = 0.05f;
    float bc = 0.0f;
};

