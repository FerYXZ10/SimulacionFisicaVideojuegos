#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "Firework.h"
#include "GravityForceGenerator.h"
#include "VortexForceGenerator.h"
#include "ExplosionForceGenerator.h"
class Scene2 : public Scene
{
private:
    std::vector<ParticleSystem*> systems;
    std::vector<Firework*> fireworks;

    Vector3D explosionCenter;
    ParticleSystem* explosionSystem = nullptr;
    ExplosionForceGenerator* explosionGenerator = nullptr;
public:
    explicit Scene2(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;
};

