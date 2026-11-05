#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3D& g) noexcept : gravity(g) {}

void GravityForceGenerator::updateForce(Particle* p, double t) noexcept {
	if (p->getMass() <= 0.0f) {
		return;
	}
	p->addForce(gravity * p->getMass());
}