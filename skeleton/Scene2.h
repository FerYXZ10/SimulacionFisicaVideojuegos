#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "Firework.h"
class Scene2 : public Scene
{
private:
    std::vector<ParticleSystem*> m_systems;
    std::vector<Firework*> m_fireworks;
public:
    explicit Scene2(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;
};

