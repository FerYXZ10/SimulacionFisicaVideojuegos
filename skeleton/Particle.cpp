#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping) : pos(Pos.x, Pos.y, Pos.z), vel(Vel), acc(Acc), damping(Damping) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pos, Vector4(0.0f, 1.0f, 1.0f, 1.0f));
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
		const Vector3D newPos = pos.p + vel_implicit * t + acc * t * t;
		prevPos = pos;
		pos.p = newPos;
	}
}

void Particle::liberar() {
	if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}