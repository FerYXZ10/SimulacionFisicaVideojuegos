#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Config& conf) : config(conf), rng(std::random_device{}()), velDistribution(0.0f, std::sqrt(config.velVariance)), posDistribution(0.0f, std::sqrt(config.posVariance)) {

}

ParticleSystem::~ParticleSystem() {
	cleanup();
}

void ParticleSystem::update(double dt) {
	for (auto it = particles.begin(); it != particles.end();) {
		Particle* p = *it;

		p->clearForces();

		for (auto& fg : forceGenerators) {
			fg->updateForce(p, dt);
		}

		p->integrateVerlet(dt);
		p->addTime(dt);

		const Vector3D distance = p->getPosition() - config.origin;
		const bool outOfBounds = distance.dot(distance) > config.maxDistanceSq;

		if (!p->isAlive() || outOfBounds) {
			delete p;
			it = particles.erase(it);
		}
		else {
			++it;
		}
	}

	if (active) {
        spawnAccumulator += dt * config.spawnRate;
        while (spawnAccumulator >= 1.0) {
            generateParticle();
            spawnAccumulator -= 1.0;
        }
    }
}

Vector3D ParticleSystem::getOrigin() const noexcept {
	return config.origin;
}

void ParticleSystem::setOrigin(const Vector3D& newOrigin) noexcept {
	config.origin = newOrigin;
}

void ParticleSystem::setActive(bool act) noexcept {
	active = act;
	if (!active) {
		spawnAccumulator = 0.0;
	}
}

bool ParticleSystem::isActive() const noexcept {
	return active;
}

size_t ParticleSystem::getParticleCount() const noexcept {
	return particles.size();
}

void ParticleSystem::addForceGenerator(ForceGenerator* fg) {
	forceGenerators.push_back(fg);
}

void ParticleSystem::cleanup() noexcept {
	for (auto& particle : particles) {
		delete particle;
	}
	particles.clear();

	for (auto& fg : forceGenerators) {
		delete fg;
	}
	forceGenerators.clear();
}

void ParticleSystem::generateParticle() {
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

	particles.push_back(new Particle(pos, vel, config.damping, physx::PxSphereGeometry(config.radius), config.color, config.maxLifetime, config.mass));
}