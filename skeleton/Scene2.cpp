#include "Scene2.h"

void Scene2::init() {
	GravityForceGenerator* fountainGravity = new GravityForceGenerator(Vector3D(0.0f, -9.81f, 0.0f));
	GravityForceGenerator* fireGravity = new GravityForceGenerator(Vector3D(0.0f, 2.0f, 0.0f));

    const Vector3D windCenter = Vector3D(0.0f, 5.0f, -5.0f);
    constexpr float windRadius = 60.0f;
    WindForceGenerator* fogWind = new WindForceGenerator(Vector3D(5, 0, 0), 0.1f, 0.0f, windCenter, windRadius);
    WindForceGenerator* fireWind = new WindForceGenerator(Vector3D(5, 0, 0), 0.1f, 0.0f, windCenter, windRadius);

    const ParticleSystem::Config fountainConfig = {
        Vector3D(0, 0, 0),
        100.0f,
        0.25f,
        1.5f,
        Vector3D(0.0f, 15.0f, 0.0f),
        2.0f,
        21.0f,
        3.0,
        0.2f,
        Vector4(0.0f, 0.5f, 1.0f, 1.0f),
        1.0f,
        2.0f,
        40.0f * 40.0f
    };
	ParticleSystem* fountainSystem = new ParticleSystem(fountainConfig);
	fountainSystem->addForceGenerator(fountainGravity);
    systems.push_back(fountainSystem);

    const ParticleSystem::Config fogConfig = {
        Vector3D(0, 10, -10),
        500.0f,
        100.0f,
        27.5f,
        Vector3D(0.0f, 0.0f, 0.0f),
        0.5f,
        4.0f,
        10.0,
        0.15f,
        Vector4(0.8f, 0.8f, 0.8f, 0.1f),
        0.9f,
        0.05f,
        55.0f * 55.0f
    };
	ParticleSystem* fogSystem = new ParticleSystem(fogConfig);
	fogSystem->addForceGenerator(fogWind);
    systems.push_back(fogSystem);

    const ParticleSystem::Config fireConfig = {
        Vector3D(5, 0, -5),
        200.0f,
        0.1f,
        1.0f,
        Vector3D(0.0f, 5.0f, 0.0f),
        3.0f,
        13.0f,
        3.0,
        0.4f,
        Vector4(1.0f, 0.3f, 0.0f, 1.0f),
        1.0f,
        0.1f,
        15.0f * 15.0f
    };
	ParticleSystem* fireSystem = new ParticleSystem(fireConfig);
	fireSystem->addForceGenerator(fireGravity);
	fireSystem->addForceGenerator(fireWind);
    systems.push_back(fireSystem);
}

void Scene2::update(double dt) {
    for (auto& system : systems) {
        system->update(dt);
    }

    for (auto it = fireworks.begin(); it != fireworks.end();) {
        Firework* fw = *it;
        fw->update(dt);

        if (fw->isFinished()) {
            delete fw;
            it = fireworks.erase(it);
        }
        else {
            ++it;
        }
    }
}

void Scene2::keyPress(unsigned char key, const physx::PxTransform& camera) {
    switch (key) {
        case 'f':
        case 'F':
            if (systems.size() > 0) {
                systems[0]->setActive(!systems[0]->isActive());
            }
            break;

        case 'n':
        case 'N':
            if (systems.size() > 1) {
                systems[1]->setActive(!systems[1]->isActive());
            }
            break;

        case 'g':
        case 'G':
            if (systems.size() > 2) {
                systems[2]->setActive(!systems[2]->isActive());
            }
            break;

        case 'r':
        case 'R': {
            const ParticleSystem::Config expConfig = {
                Vector3D(0, 0, 0),
                30000.0f,
                1.0f,
                2.0f,
                Vector3D(0, 0, 0),
                30.0f, 30.0f,
                5.0,
                0.5f,
                Vector4(1.0f, 0.5f, 0.0f, 1.0f),
                0.95f,
				0.1f,
                200.0f * 200.0f
            };

            const Firework::Config fwConfig = {
                Vector3D(0.0f, 0.0f, 0.0f),
                1.0f,
                5.5f,
                Vector3D(0.0f, 50.0f, 0.0f),
                20.0f,
                62.5f,
                1.0f,
				Vector4(1.0f, 1.0f, 1.0f, 1.0f),
                1.0f,
                1.0f,
                std::vector<Vector4>{
                    Vector4(1.0f, 0.0f, 0.0f, 1.0f),
                    Vector4(0.0f, 1.0f, 0.0f, 1.0f),
                    Vector4(0.0f, 0.0f, 1.0f, 1.0f),
                    Vector4(1.0f, 1.0f, 0.0f, 1.0f),
                    Vector4(1.0f, 0.0f, 1.0f, 1.0f),
                    Vector4(0.0f, 1.0f, 1.0f, 1.0f),
                    Vector4(1.0f, 0.5f, 0.0f, 1.0f),
                    Vector4(1.0f, 0.0f, 0.5f, 1.0f),
                    Vector4(0.5f, 1.0f, 0.0f, 1.0f),
                    Vector4(0.5f, 0.0f, 1.0f, 1.0f),
                    Vector4(0.0f, 1.0f, 0.5f, 1.0f),
                    Vector4(0.0f, 0.5f, 1.0f, 1.0f)
                }
			};
			Firework* fwSystem = new Firework(fwConfig, expConfig);
			GravityForceGenerator* fwGravity = new GravityForceGenerator(Vector3D(0.0f, -9.81f, 0.0f));
			fwSystem->addForceGenerator(fwGravity);

            fireworks.push_back(fwSystem);

            break;
        }

        default:
            break;
    }
}

void Scene2::cleanup() {
    for (auto& system : systems) {
        delete system;
    }
    systems.clear();

    for (auto& fw : fireworks) {
        delete fw;
    }
    fireworks.clear();

    Scene::cleanup();
}