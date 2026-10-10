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

void Particle::liberar() {
	if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}