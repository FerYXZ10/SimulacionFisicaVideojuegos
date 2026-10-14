#pragma once

#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Acc, float Damping);
	~Particle();

	void integrateEuler(double t);
	void integrateSemiImplicitEuler(double t);
	void integrateVerlet(double t);

private:
	Vector3D vel;
	Vector3D acc;
	float damping;
	physx::PxTransform prevPos;
	physx::PxTransform pos;
	bool isFirstIntegration = true;
	RenderItem* renderItem;

	void liberar();
};

