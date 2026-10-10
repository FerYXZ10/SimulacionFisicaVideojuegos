#pragma once

#include "RenderUtils.hpp"
#include "Vector3D.h"

class Particle
{
public:
	Particle(Vector3D Pos, Vector3D Vel);
	~Particle();

	void integrateEuler(double t);

private:
	Vector3D vel;
	physx::PxTransform pos;
	RenderItem* renderItem;

	void liberar();
};

