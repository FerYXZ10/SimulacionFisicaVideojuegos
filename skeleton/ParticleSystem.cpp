#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Config& config) : m_config(config), m_rng(std::random_device{}()), m_velDistribution(0.0f, std::sqrt(config.velVariance)), m_posDistribution(0.0f, std::sqrt(config.posVariance)) {

}

ParticleSystem::~ParticleSystem() {
	cleanup();
}

void ParticleSystem::update(double dt) {
	for (auto it = m_particles.begin(); it != m_particles.end();) {
		Particle* p = *it;

		p->integrateVerlet(dt);
		p->addTime(dt);

		const Vector3D distance = p->getPosition() - m_config.origin;
		const bool outOfBounds = distance.dot(distance) > m_config.maxDistanceSq;

		if (!p->isAlive() || outOfBounds) {
			delete p;
			it = m_particles.erase(it);
		}
		else {
			++it;
		}
	}

	if (m_isActive) {
        m_spawnAccumulator += dt * m_config.spawnRate;
        while (m_spawnAccumulator >= 1.0) {
            generateParticle();
            m_spawnAccumulator -= 1.0;
        }
    }
}

Vector3D ParticleSystem::getOrigin() const noexcept {
	return m_config.origin;
}

void ParticleSystem::setOrigin(const Vector3D& newOrigin) noexcept {
	m_config.origin = newOrigin;
}

void ParticleSystem::setActive(bool active) noexcept {
	m_isActive = active;
	if (!m_isActive) {
		m_spawnAccumulator = 0.0;
	}
}

bool ParticleSystem::isActive() const noexcept {
	return m_isActive;
}

void ParticleSystem::cleanup() noexcept {
	for (auto& particle : m_particles) {
		delete particle;
	}
	m_particles.clear();
}

void ParticleSystem::generateParticle() {
	Vector3D offset(m_posDistribution(m_rng), m_posDistribution(m_rng), m_posDistribution(m_rng));

	const float mag = offset.magnitude();
	if (mag > m_config.maxPosOffset) {
		offset *= (m_config.maxPosOffset / mag);
	}

	const Vector3D pos = m_config.origin + offset;

	Vector3D vel(m_config.meanVelocity.x + m_velDistribution(m_rng), m_config.meanVelocity.y + m_velDistribution(m_rng), m_config.meanVelocity.z + m_velDistribution(m_rng));
	if (vel.magnitude() > m_config.maxVelMagnitude) {
		vel.normalize();
		vel *= m_config.maxVelMagnitude;
	}

	m_particles.push_back(new Particle(pos, vel, m_config.gravity, m_config.damping, physx::PxSphereGeometry(m_config.radius), m_config.color, m_config.maxLifetime));
}