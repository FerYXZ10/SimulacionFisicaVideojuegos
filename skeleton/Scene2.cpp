#include "Scene2.h"

void Scene2::init() {
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
        Vector3D(0.0f, -10.0f, 0.0f),
        1.0f,
        40.0f * 40.0f
    };
    m_systems.push_back(new ParticleSystem(fountainConfig));

    const ParticleSystem::Config fogConfig = {
        Vector3D(0, 10, -10),
        1000.0f,
        100.0f,
        27.5f,
        Vector3D(0.0f, 0.0f, 0.0f),
        0.5f,
        4.0f,
        3.0,
        0.15f,
        Vector4(0.8f, 0.8f, 0.8f, 0.1f),
        Vector3D(0.0f, 0.0f, 0.0f),
        0.9f,
        50.0f * 50.0f
    };
    m_systems.push_back(new ParticleSystem(fogConfig));

    const ParticleSystem::Config fireConfig = {
        Vector3D(5, 0, -5),
        200.0f,
        0.1f,
        1.0f,
        Vector3D(0.0f, 5.0f, 0.0f),
        3.0f,
        13.0f,
        1.0,
        0.4f,
        Vector4(1.0f, 0.3f, 0.0f, 1.0f),
        Vector3D(0.0f, 2.0f, 0.0f),
        1.0f,
        15.0f * 15.0f
    };
    m_systems.push_back(new ParticleSystem(fireConfig));
}

void Scene2::update(double dt) {
    for (auto& system : m_systems) {
        system->update(dt);
    }

    for (auto it = m_fireworks.begin(); it != m_fireworks.end();) {
        Firework* fw = *it;
        fw->update(dt);

        if (fw->isFinished()) {
            delete fw;
            it = m_fireworks.erase(it);
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
            if (m_systems.size() > 0) {
                m_systems[0]->setActive(!m_systems[0]->isActive());
            }
            break;

        case 'n':
        case 'N':
            if (m_systems.size() > 1) {
                m_systems[1]->setActive(!m_systems[1]->isActive());
            }
            break;

        case 'g':
        case 'G':
            if (m_systems.size() > 2) {
                m_systems[2]->setActive(!m_systems[2]->isActive());
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
                Vector3D(0.0f, -9.81f, 0.0f),
                0.95f,
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
				Vector3D(0.0f, -9.81f, 0.0f),
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

            m_fireworks.push_back(new Firework(fwConfig, expConfig));
            break;
        }

        default:
            break;
    }
}

void Scene2::cleanup() {
    for (auto& system : m_systems) {
        delete system;
    }
    m_systems.clear();
    for (auto& fw : m_fireworks) {
        delete fw;
    }
    m_fireworks.clear();
    Scene::cleanup();
}