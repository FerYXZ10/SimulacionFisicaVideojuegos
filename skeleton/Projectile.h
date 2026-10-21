#pragma once
#include "Particle.h"
class Projectile : public Particle
{
public:
	Projectile(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping, float SimulatedVel, float RealMass, float RealGravity);
	~Projectile() = default;

	void setRealVel(float speed);

private:
	float realMass;
	float simulatedMass;

	float realGravity;
	float simulatedGravity;

	float realVel;
	float simulatedVel;
};

