#include "Projectile.h"

Projectile::Projectile(Vector3D Pos, Vector3D Vel, float Damping, const physx::PxGeometry& Geo, Vector4 Color, float SimulatedVel, float RealMass, float RealGravity) : Particle(Pos, Vel, Damping, Geo, Color), simulatedVel(SimulatedVel), realMass(RealMass), realGravity(RealGravity) {
	realVel = Vel.magnitude();
	const float simulatedMassRatio = realVel / simulatedVel;
	const float simulatedGravityRatio = simulatedVel / realVel;
	simulatedMass = realMass * simulatedMassRatio * simulatedMassRatio;
	simulatedGravity = realGravity * simulatedGravityRatio * simulatedGravityRatio;
	Vector3D dir = Vel;
	dir.normalize();
	vel = dir * simulatedVel;
	mass = simulatedMass;
}

Projectile::Projectile(Vector3D Pos, Vector3D Vel, float Damping, float SimulatedVel, float RealMass, float RealGravity) : Projectile(Pos, Vel, Damping, physx::PxSphereGeometry(1.0f), Vector4(0.0f, 1.0f, 1.0f, 1.0f), SimulatedVel, RealMass, RealGravity) {
	
}

void Projectile::setRealVel(float speed) noexcept {
	realVel = speed;
	const float simulatedMassRatio = realVel / simulatedVel;
	const float simulatedGravityRatio = simulatedVel / realVel;
	simulatedMass = realMass * simulatedMassRatio * simulatedMassRatio;
	simulatedGravity = realGravity * simulatedGravityRatio * simulatedGravityRatio;
	Vector3D dir = vel;
	dir.normalize();
	vel = dir * simulatedVel;
	mass = simulatedMass;
}

float Projectile::getSimulatedGravity() const noexcept {
	return simulatedGravity;
}