#include "Firework.h"

Firework::Firework(const Config& conf, const ParticleSystem::Config& explConfig) : config(conf), rng(std::random_device{}()), velDistribution(0.0f, std::sqrt(config.velVariance)), posDistribution(0.0f, std::sqrt(config.posVariance)), explosionConfig(explConfig)
{
	Vector3D offset(posDistribution(rng), posDistribution(rng), posDistribution(rng));

	const float mag = offset.magnitude();
    if (mag > config.maxPosOffset) {
        offset *= (config.maxPosOffset / mag);
	}

	const Vector3D pos = config.origin + offset;

    Vector3D vel(config.meanVelocity.x + velDistribution(rng), config.meanVelocity.y + velDistribution(rng), config.meanVelocity.z + velDistribution(rng));
    if (vel.magnitude() > config.maxVelMagnitude) {
        vel.normalize();
        vel *= config.maxVelMagnitude;
    }

	const double lifeTime = std::abs(vel.y / 9.81f);

    rocket = new Particle(
        pos,
        vel,
        config.damping,
        physx::PxSphereGeometry(config.radius),
        config.color,
        lifeTime,
        config.mass
    );
}

Firework::~Firework() {
    delete rocket;

    for (auto& exp : explosions) {
        delete exp.first;
    }
    explosions.clear();

    for (auto& fg : forceGenerators) {
        delete fg;
	}
	forceGenerators.clear();
}

void Firework::update(double dt) {
    if (rocket) {
        for (auto fg : forceGenerators) {
            fg->tick(dt);
        }

        rocket->clearForces();

        for (auto fg : forceGenerators) {
            fg->updateForce(rocket);
        }

        rocket->integrateVerlet(dt);
        rocket->addTime(dt);

        if (!rocket->isAlive()) {
            explosionConfig.origin = rocket->getPosition();

            if (!config.explosionColors.empty()) {
                std::uniform_int_distribution<size_t> colorIndex(0, config.explosionColors.size() - 1);
                explosionConfig.color = config.explosionColors[colorIndex(rng)];
            }

			explosionConfig.maxLifetime = std::sqrt(std::abs(2.0f * explosionConfig.origin.y / 9.81f)) + 1.5f;

			const float maxDistance = explosionConfig.origin.y * 1.075f;
			explosionConfig.maxDistanceSq = maxDistance * maxDistance;

			ParticleSystem* explosionSystem = new ParticleSystem(explosionConfig);
            explosionSystem->addForceGenerator(new GravityForceGenerator(Vector3D(0.0f, -9.81f, 0.0f)));

            explosions.push_back({ explosionSystem, 0.05f });

            delete rocket;
            rocket = nullptr;
        }
    }

    for (auto it = explosions.begin(); it != explosions.end();) {
        ParticleSystem* exp = it->first;
        float& timer = it->second;

        exp->tick(dt);
        exp->update(dt);
        timer -= dt;

        if (timer <= 0.0f && exp->isActive()) {
            exp->setActive(false);
        }

        if (!exp->isActive() && exp->getParticleCount() == 0) {
            delete exp;
            it = explosions.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool Firework::isFinished() const {
    return rocket == nullptr && explosions.empty();
}

void Firework::addForceGenerator(ForceGenerator* fg) {
    forceGenerators.push_back(fg);
}