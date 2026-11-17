#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(float _k, float restingL, Particle* p, float dampingRat) noexcept : k(_k), restingLength(restingL), other(p), dampingRatio(dampingRat), bc(0.0f) {}

void SpringForceGenerator::updateForce(Particle* p) {
	if (p->getMass() <= 0.0f || other == nullptr) {
		return;
	}

	const Vector3D d = p->getPosition() - other->getPosition();
	const float currentLength = d.magnitude();
	if (currentLength < 1e-6f) {
		return;
	}

	const Vector3D dir = d / currentLength;

	Vector3D force = -k * (currentLength - restingLength) * dir;

	const float mEff = (p->getMass() * other->getMass()) / (p->getMass() + other->getMass());
	bc = 2.0f * std::sqrt(std::abs(k * mEff));
	const Vector3D vRel = p->getVel() - other->getVel();
	force -= dampingRatio * bc * vRel;

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