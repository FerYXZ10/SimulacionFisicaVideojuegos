#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, float Damping, const physx::PxGeometry& Geo, Vector4 Color, double LifeTime, float Mass) : pos(Pos.x, Pos.y, Pos.z), vel(Vel), damping(Damping), maxLifeTime(LifeTime), mass(Mass) {
	renderItem = new RenderItem(CreateShape(Geo), &pos, Color);
}

Particle::~Particle() {
	liberar();
}

void Particle::integrateEuler(double t) {
	pos.p += vel * t;
	vel = vel * pow(damping, t) + (forceAccumulator / mass) * t;
}

void Particle::integrateSemiImplicitEuler(double t) {
	vel = vel * pow(damping, t) + (forceAccumulator / mass) * t;
	pos.p += vel * t;
}

void Particle::integrateVerlet(double t) {
	if (isFirstIntegration) {
		prevPos = pos;
		integrateSemiImplicitEuler(t);
		isFirstIntegration = false;
	}
	else {
		Vector3D vel_implicit = (pos.p - prevPos.p) / static_cast<float>(t);
		vel_implicit *= static_cast<float>(pow(damping, t));
		const Vector3D a(forceAccumulator / mass);
		vel = vel_implicit + a * t;
		const Vector3D newPos = pos.p + vel_implicit * t + a * t * t;
		prevPos = pos;
		pos.p = newPos;
	}
}

void Particle::addTime(double t) noexcept {
	if (maxLifeTime > 0.0) {
		aliveTime += t;
	}
}

bool Particle::isAlive() const noexcept {
	return maxLifeTime <= 0.0 || aliveTime < maxLifeTime;
}

Vector3D Particle::getPosition() const {
	return pos.p;
}

Vector3D Particle::getVel() const noexcept {
	return vel;
}

float Particle::getMass() const noexcept {
	return mass;
}

void Particle::clearForces() noexcept {
	forceAccumulator = Vector3D(0, 0, 0);
}

void Particle::addForce(const Vector3D& f) noexcept {
	forceAccumulator += f;
}

void Particle::liberar() {
	if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}