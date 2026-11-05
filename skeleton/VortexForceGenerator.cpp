#include "VortexForceGenerator.h"

VortexForceGenerator::VortexForceGenerator(const Vector3D& cent, float radius, float str, float _k1, float _k2) noexcept : WindForceGenerator(Vector3D(0.0f, 0.0f, 0.0f), _k1, _k2, cent, radius), strength(str) {}

Vector3D VortexForceGenerator::computeWindVel(const Vector3D& position) const noexcept {
    const Vector3D rel = position - influenceCenter;

    return Vector3D(-strength * rel.z, strength * (50.0f - rel.y), strength * rel.x);
}

void VortexForceGenerator::updateForce(Particle* p) {
    if (p->getMass() <= 0.0f) {
        return;
    }

    const Vector3D toCenter = p->getPosition() - influenceCenter;
    if (toCenter.dot(toCenter) > influenceRadiusSq) {
        return;
    }

    const Vector3D wind = computeWindVel(p->getPosition());
    const Vector3D relativeVel = wind - p->getVel();

    Vector3D force = k1 * relativeVel;

    if (k2 != 0.0f) {
        force += k2 * relativeVel.magnitude() * relativeVel;
    }

    p->addForce(force);
}