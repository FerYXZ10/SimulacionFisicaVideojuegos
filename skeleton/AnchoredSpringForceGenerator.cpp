#include "AnchoredSpringForceGenerator.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(float _k, float restingL, const Vector3D& anchorP, float anchorTotalSize, Vector4 color, float dampingRat) : SpringForceGenerator(_k, restingL, nullptr, dampingRat), anchorPos(anchorP), renderItem(nullptr), anchorTransform(anchorP.x, anchorP.y, anchorP.z)
{
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(Vector3D(anchorTotalSize * 0.5f, anchorTotalSize * 0.5f, anchorTotalSize * 0.5f)));
	renderItem = new RenderItem(shape, &anchorTransform, color);
	shape->release();
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {
	if (renderItem) {
		renderItem->release();
		renderItem = nullptr;
	}
}

void AnchoredSpringForceGenerator::updateForce(Particle* p) {
	if (p->getMass() <= 0.0f) {
		return;
	}

	const Vector3D d = p->getPosition() - anchorPos;
	const float currentLength = d.magnitude();
	if (currentLength < 1e-6f) {
		return;
	}

	Vector3D force = -k * (currentLength - restingLength) * (d / currentLength);

	bc = 2.0f * std::sqrt(std::abs(k * p->getMass()));
	force -= dampingRatio * bc * p->getVel();

	p->addForce(force);
}