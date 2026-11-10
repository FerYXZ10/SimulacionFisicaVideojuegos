#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringForceGenerator : public SpringForceGenerator
{
public:
    AnchoredSpringForceGenerator(float _k, float restingL, const Vector3D& anchorP, float anchorTotalSize = 1.0f, Vector4 color = Vector4(0.0f, 0.0f, 1.0f, 1.0f), float dampingRat = 0.05f);
    virtual ~AnchoredSpringForceGenerator();

    virtual void updateForce(Particle* p) override;

private:
    Vector3D anchorPos;

	RenderItem* renderItem;
    physx::PxTransform anchorTransform;
};

