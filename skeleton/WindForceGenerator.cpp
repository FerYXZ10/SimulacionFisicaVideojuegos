#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(const Vector3D& windV, float _k1, float _k2) noexcept : windVel(windV), k1(_k1), k2(_k2) {}

void WindForceGenerator::updateForce(Particle* p, double t) noexcept {
	if (p->getMass() <= 0.0f) {
		return;
	}

	const Vector3D relativeVel = windVel - p->getVel();
	Vector3D force = k1 * relativeVel;
	if (k2 != 0.0f) {
		force += (k2 * relativeVel.magnitude() * relativeVel);
	}
	p->addForce(force);
}