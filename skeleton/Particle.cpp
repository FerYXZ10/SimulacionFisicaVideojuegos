#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel) : pos(Pos.x, Pos.y, Pos.z), vel(Vel) {
	renderItem = new RenderItem(CreateShape(physx::PxSphereGeometry(1.0f)), &pos, Vector4(0.0f, 1.0f, 1.0f, 1.0f));
}

Particle::~Particle() {
	liberar();
}

void Particle::integrateEuler(double t) {
	pos.p += vel * t;
}

void Particle::liberar() {
	if (renderItem) {
        renderItem->release();
        renderItem = nullptr;
    }
}