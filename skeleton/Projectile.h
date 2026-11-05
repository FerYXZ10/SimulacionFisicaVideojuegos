#pragma once
#include "Particle.h"
class Projectile : public Particle
{
public:
	struct Config {
		float realVel;
		float damping;
		Vector4 color;
		float simVel;
		float realMass;
		float realGravity;
	};

	Projectile(Vector3D Pos, Vector3D Vel, float Damping, const physx::PxGeometry& Geo, Vector4 Color, float SimulatedVel, float RealMass, float RealGravity);
	Projectile(Vector3D Pos, Vector3D Vel, float Damping, float SimulatedVel, float RealMass, float RealGravity);
	~Projectile() = default;

	void setRealVel(float speed);
	float getSimulatedGravity() const noexcept;

private:
	float realMass;
	float simulatedMass;

	float realGravity;
	float simulatedGravity;

	float realVel;
	float simulatedVel;
};

