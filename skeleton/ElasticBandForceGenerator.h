#pragma once
#include "SpringForceGenerator.h"
class ElasticBandForceGenerator : public SpringForceGenerator
{
public:
    using SpringForceGenerator::SpringForceGenerator;

    void updateForce(Particle* p) override;
};

