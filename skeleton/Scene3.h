#pragma once
#include "Scene.h"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "WindForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
#include "ElasticBandForceGenerator.h"
class Scene3 : public Scene
{
private:
    GravityForceGenerator* gravity = nullptr;
    WindForceGenerator* wind = nullptr;

	float impulseTimerSetup = 0.0f;
	float impulseTimerPair = 0.0f;
	int integrationMethod = 2; // 0: Euler, 1: Semi-Implicit Euler, 2: Verlet
    bool windActive = false;
    int windDirIndex = 0;

    struct SpringSetup {
        AnchoredSpringForceGenerator* anchoredSpring;
        Particle* particle;
    };

	std::vector<SpringSetup> setups;

    struct SpringPair {
        Particle* particleA;
        Particle* particleB;
        SpringForceGenerator* springFromA;
        SpringForceGenerator* springFromB;
        SpringForceGenerator* bandFromA;
        SpringForceGenerator* bandFromB;
        bool useBand = false;
    };

    std::vector<SpringPair> pairs;

    void updateDisplayText();
public:
    explicit Scene3(std::string name) : Scene(std::move(name)) {}

    ~Scene3() override;

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;
};

