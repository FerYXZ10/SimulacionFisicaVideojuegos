#include "WindForceGenerator.h"

WindForceGenerator::WindForceGenerator(const Vector3D& windV, float _k1, float _k2, const Vector3D& center, float radius) noexcept : windVel(windV), k1(_k1), k2(_k2), influenceCenter(center), influenceRadius(radius), influenceRadiusSq(radius * radius) {}

void WindForceGenerator::updateForce(Particle* p, double t) {
	if (p->getMass() <= 0.0f) {
		return;
	}

	const Vector3D toCenter = p->getPosition() - influenceCenter;
	if (toCenter.dot(toCenter) > influenceRadiusSq) {
		return;
	}

	const Vector3D relativeVel = windVel - p->getVel();
	Vector3D force = k1 * relativeVel;
	if (k2 != 0.0f) {
		force += (k2 * relativeVel.magnitude() * relativeVel);
	}
	p->addForce(force);
}