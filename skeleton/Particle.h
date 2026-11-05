#pragma once

#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, float Damping, const physx::PxGeometry& Geo = physx::PxSphereGeometry(1.0f), Vector4 Color = Vector4(0.0f, 1.0f, 1.0f, 1.0f), double LifeTime = 0.0f, float Mass = 1.0f);
	~Particle();

	void integrateEuler(double t);
	void integrateSemiImplicitEuler(double t);
	void integrateVerlet(double t);

	void addTime(double t) noexcept;
	bool isAlive() const noexcept;

	Vector3D getPosition() const;
	Vector3D getVel() const noexcept;
	float getMass() const noexcept;

	void clearForces() noexcept;
	void addForce(const Vector3D& f) noexcept;

protected:
	Vector3D vel;

	float damping;

	physx::PxTransform prevPos;
	physx::PxTransform pos;

	bool isFirstIntegration = true;

	double aliveTime = 0.0;
	double maxLifeTime = 0.0;

	float mass = 1.0f;

	Vector3D forceAccumulator = Vector3D(0.0f, 0.0f, 0.0f);

	RenderItem* renderItem;

	void liberar();
};

