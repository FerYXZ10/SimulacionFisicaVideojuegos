#include "Scene0.h"

void Scene0::init() {
    m_transforms.reserve(1+ 3 + 4 + N);

    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
    m_transforms.push_back(physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f)));

    m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(1.0f, 0.0f, 1.0f, 1.0f)));

    // Reto A
	w = u.cross(v);

	u.normalize();
	v.normalize();
	w.normalize();

    u *= 5.0f;
	v *= 5.0f;
	w *= 5.0f;

	physx::PxShape* shapeA = CreateShape(physx::PxSphereGeometry(1.0f));

	m_transforms.push_back(physx::PxTransform(u));
	m_renderItems.push_back(new RenderItem(shapeA, &m_transforms.back(), Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

	m_transforms.push_back(physx::PxTransform(v));
	m_renderItems.push_back(new RenderItem(shapeA, &m_transforms.back(), Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

	m_transforms.push_back(physx::PxTransform(w));
	m_renderItems.push_back(new RenderItem(shapeA, &m_transforms.back(), Vector4(0.0f, 0.0f, 1.0f, 1.0f)));

    // Reto B
    Vector3D objetivos[] = {
        Vector3D(2.0f, 0.0f,  3.0f),
        Vector3D(-4.0f, 0.0f,  1.0f),
        Vector3D(0.0f, 0.0f, -5.0f),
        Vector3D(3.0f, 0.0f,  0.0f)
    };

    for (const Vector3D& P : objetivos) {
        Vector3D V = P - E;

        float dot = D.dot(V);

        Vector4 color;
        if (dot > 0.0f) {
            color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else if (dot < 0.0f) {
            color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else {
            color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
        }

        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
        m_transforms.push_back(physx::PxTransform(P.x, P.y, P.z));
        m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), color));
    }

    // Reto C
    for (int i = 0; i < N; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(N - 1);

        Vector3D P = A + (B - A) * t;

        physx::PxShape* shapeC = CreateShape(physx::PxSphereGeometry(0.3f));
        m_transforms.push_back(physx::PxTransform(P.x, P.y, P.z));
        m_renderItems.push_back(new RenderItem(shapeC, &m_transforms.back(), Vector4(1.0f, 1.0f, 0.0f, 1.0f)));
    }
}

void Scene0::update(double dt) {
    
}

void Scene0::keyPress(unsigned char key, const physx::PxTransform& camera) {
    if (key == 'r' || key == 'R') {
        for (auto& transform : m_transforms) {
            transform.p = physx::PxVec3(0.0f, 0.0f, 0.0f); // Reset
		}
    }
}