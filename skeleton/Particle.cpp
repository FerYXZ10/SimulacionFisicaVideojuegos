#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping, const physx::PxGeometry& Geo, Vector4 Color, double LifeTime) : pos(Pos.x, Pos.y, Pos.z), vel(Vel), acc(Acc), damping(Damping), maxLifeTime(LifeTime) {
	renderItem = new RenderItem(CreateShape(Geo), &pos, Color);
}

Particle::~Particle() {
	liberar();
}

void Particle::integrateEuler(double t) {
	pos.p += vel * t;
	vel = vel * pow(damping, t) + acc * t;
}

void Particle::integrateSemiImplicitEuler(double t) {
	vel = vel * pow(damping, t) + acc * t;
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
		vel = vel_implicit + acc * t;
		const Vector3D newPos = pos.p + vel_implicit * t + acc * t * t;
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

void Particle::liberar() {
	if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}