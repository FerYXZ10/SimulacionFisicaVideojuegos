#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(float _k, float restingL, Particle* p, float dampingRat) noexcept : k(_k), restingLength(restingL), other(p), dampingRatio(dampingRat), bc(0.0f) {}

void SpringForceGenerator::updateForce(Particle* p) {
	if (p->getMass() <= 0.0f) {
		return;
	}

	if (other == nullptr) {
		return;
	}

	const Vector3D d = p->getPosition() - other->getPosition();
	const float currentLength = d.magnitude();
	if (currentLength < 1e-6f) {
		return;
	}

	Vector3D force = -k * (currentLength - restingLength) * (d / currentLength);

	bc = 2.0f * std::sqrt(std::abs(k * p->getMass()));
	force -= dampingRatio * bc * p->getVel();

	p->addForce(force);
}

float SpringForceGenerator::getK() const noexcept {
	return k;
}

void SpringForceGenerator::setK(float _k) noexcept {
	k = std::max<float>(_k, 0.1f);
}

float SpringForceGenerator::getDampingRatio() const noexcept {
	return dampingRatio;
}

void SpringForceGenerator::setDampingRatio(float ratio) noexcept {
	dampingRatio = std::max<float>(ratio, 0.0f);
}