#pragma once
#include "Scene.h"
#include "Particle.h"
#include "GravityForceGenerator.h"
#include "AnchoredSpringForceGenerator.h"
class Scene3 : public Scene
{
private:
    GravityForceGenerator* gravity = nullptr;

	float impulseTimer = 0.0f;
	int integrationMethod = 2; // 0: Euler, 1: Semi-Implicit Euler, 2: Verlet

    struct SpringSetup {
        AnchoredSpringForceGenerator* anchoredSpring;
        Particle* particle;
    };

	std::vector<SpringSetup> setups;
public:
    explicit Scene3(std::string name) : Scene(std::move(name)) {}

    ~Scene3() override;

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;
};

