#include "Scene1.h"

void Scene1::init() {
	m_transforms.reserve(3);

	// Suelo
	physx::PxShape* floorShape = CreateShape(physx::PxBoxGeometry(50.0f, 1.0f, 50.0f));
	m_transforms.push_back(physx::PxTransform(physx::PxVec3(0.0f, -1.0f, 0.0f)));
	m_renderItems.push_back(new RenderItem(floorShape, &m_transforms.back(), Vector4(0.2f, 0.6f, 0.2f, 1.0f)));

	// Diana
	physx::PxShape* targetShape = CreateShape(physx::PxBoxGeometry(3.0f, 3.0f, 0.25f));
	m_transforms.push_back(physx::PxTransform(physx::PxVec3(0.0f, 5.0f, -30.0f)));
	m_renderItems.push_back(new RenderItem(targetShape, &m_transforms.back(), Vector4(0.9f, 0.1f, 0.1f, 1.0f)));

	// Centro de la diana
	physx::PxShape* centerShape = CreateShape(physx::PxSphereGeometry(1.0f));
	m_transforms.push_back(physx::PxTransform(physx::PxVec3(0.0f, 5.0f, -29.75f)));
	m_renderItems.push_back(new RenderItem(centerShape, &m_transforms.back(), Vector4(1.0f, 0.8f, 0.0f, 1.0f)));
}

void Scene1::update(double dt) {
	for (auto& projectile : m_projectiles) {
		projectile->clearForces();
		projectile->addForce(Vector3D(0.0f, -projectile->getSimulatedGravity() * projectile->getMass(), 0.0f));
		projectile->integrateVerlet(dt);
	}
}

void Scene1::keyPress(unsigned char key, const physx::PxTransform& camera) {
	switch (key) {
		case 'f':
		case 'F': {
			const Projectile::Config pistol = { 300.0f, 1.0f, Vector4(1.0f, 1.0f, 0.0f, 1.0f), 15.0f, 0.008f, 9.81f };
			fire(pistol, physx::PxSphereGeometry(1.0f), camera);
			break;
		}

		case 'j':
		case 'J': {
			const Projectile::Config canon = { 50.0f, 1.0f, Vector4(0.4f, 0.4f, 0.4f, 1.0f), 10.0f, 17.5f, 9.81f };
			fire(canon, physx::PxSphereGeometry(2.0f), camera);
			break;
		}

		default:
			break;
	}
}

void Scene1::cleanup() {
	for (auto& projectile : m_projectiles) {
		delete projectile;
	}
	m_projectiles.clear();
	Scene::cleanup();
}

void Scene1::fire(const Projectile::Config& config, const physx::PxGeometry& geo, const physx::PxTransform& camera) {
	const Vector3D camPos(camera.p);
	const Vector3D camDir = Vector3D(camera.q.rotate(physx::PxVec3(0.0f, 0.0f, -1.0f)));
	const Vector3D spawnPos = camPos + camDir * 2.0f;

	m_projectiles.push_back(new Projectile(
		spawnPos,
		camDir * config.realVel,
		config.damping,
		geo,
		config.color,
		config.simVel,
		config.realMass,
		config.realGravity
	));
}