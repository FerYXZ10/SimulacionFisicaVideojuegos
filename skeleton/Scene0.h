#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include <vector>

class Scene0 : public Scene
{
public:
    explicit Scene0(std::string name) : Scene(std::move(name)) {}

    void init() override;

    void update(double dt) override;

    void keyPress(unsigned char key, const physx::PxTransform& camera) override;

private:
    Vector3D u = Vector3D(3, 1, 0);
	Vector3D v = Vector3D(0, 4, 0);
	Vector3D w = Vector3D();

	Vector3D D = Vector3D(0.0f, 0.0f, 1.0f);
	Vector3D E = Vector3D(0.0f, 0.0f, 0.0f);

	Vector3D A = Vector3D(-8.0f, 1.0f, -8.0f);
	Vector3D B = Vector3D(8.0f, 8.0f, 8.0f);
	const int N = 10;
};

