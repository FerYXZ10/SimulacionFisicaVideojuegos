#include "Projectile.h"

Projectile::Projectile(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping, float SimulatedVel, float RealMass, float RealGravity) : Particle(Pos, Vel, Acc, Damping), simulatedVel(SimulatedVel), realMass(RealMass), realGravity(RealGravity) {
	realVel = Vel.magnitude();
	simulatedMass = realMass * pow(realVel / simulatedVel, 2.0f);
	simulatedGravity = realGravity * pow(simulatedVel / realVel, 2.0f);
	Vector3D dir = Vel;
	dir.normalize();
	vel = dir * simulatedVel;
	acc = Vector3D(0.0f, -simulatedGravity, 0.0f);
}

void Projectile::setRealVel(float speed) {
	realVel = speed;
	simulatedMass = realMass * pow(realVel / simulatedVel, 2.0f);
	simulatedGravity = realGravity * pow(simulatedVel / realVel, 2.0f);
	Vector3D dir = vel;
	dir.normalize();
	vel = dir * simulatedVel;
	acc = Vector3D(0.0f, -simulatedGravity, 0.0f);
}