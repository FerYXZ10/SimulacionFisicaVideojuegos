#pragma once

#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping, const physx::PxGeometry& Geo = physx::PxSphereGeometry(1.0f), Vector4 Color = Vector4(0.0f, 1.0f, 1.0f, 1.0f), double LifeTime = 0.0f);
	~Particle();

	void integrateEuler(double t);
	void integrateSemiImplicitEuler(double t);
	void integrateVerlet(double t);

	void addTime(double t) noexcept;
	bool isAlive() const noexcept;

	Vector3D getPosition() const;
	Vector3D getVel() const noexcept;

protected:
	Vector3D vel;
	Vector3D acc;

	float damping;

	physx::PxTransform prevPos;
	physx::PxTransform pos;

	bool isFirstIntegration = true;

	double aliveTime = 0.0;
	double maxLifeTime = 0.0;

	RenderItem* renderItem;

	void liberar();
};

