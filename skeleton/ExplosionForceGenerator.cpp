#include "ExplosionForceGenerator.h"

ExplosionForceGenerator::ExplosionForceGenerator(const Vector3D& center, float rad, float _k, float tau) noexcept : center(center), radius(rad), k(_k), tau(tau), radiusSq(rad * rad) {}

Vector3D ExplosionForceGenerator::computeExplosionForce(const Vector3D& position, double elapsed) const noexcept {
    const Vector3D rel = position - center;
    const float rSq = rel.dot(rel);

    if (rSq < 1e-6f) {
        return Vector3D(0.0f, 0.0f, 0.0f);
    }

    const float factor1 = k / rSq;
    const float factor2 = std::exp(-static_cast<float>(elapsed) / tau);

    return rel * factor1 * factor2;
}

void ExplosionForceGenerator::tick(double dt) noexcept {
    elapsedTime += static_cast<float>(dt);
}

bool ExplosionForceGenerator::isFinished() const noexcept {
    return elapsedTime > 4.0f * tau;
}

void ExplosionForceGenerator::updateForce(Particle* p) {
    if (p->getMass() <= 0.0f) {
        return;
    }

    if (elapsedTime > 4.0f * tau) {
        return;
    }

    const Vector3D toCenter = p->getPosition() - center;
    if (toCenter.dot(toCenter) > radiusSq) {
        return;
    }

    p->addForce(computeExplosionForce(p->getPosition(), elapsedTime));
}