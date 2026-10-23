#pragma once
#include "Scene.h"
#include "Projectile.h"

class Scene1 : public Scene
{
private:
    std::vector<Projectile*> m_projectiles;

    void fire(const Projectile::Config& config, const physx::PxGeometry& geo, const physx::PxTransform& camera);

public:
    explicit Scene1(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

    void cleanup() override;
};


