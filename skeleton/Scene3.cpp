#include "Scene3.h"

Scene3::~Scene3() {
	Scene3::cleanup();
}

void Scene3::init() {
	if (!setups.empty()) {
		return;
	}

	gravity = new GravityForceGenerator(Vector3D(0.0f, -9.81f, 0.0f));

	const Vector3D anchorP1 = Vector3D(-5.0f, 5.0f, 0.0f);
	const float restingL1 = 5.0f;

	AnchoredSpringForceGenerator* anchoredSpring1 = new AnchoredSpringForceGenerator(10.0f, restingL1, anchorP1, 0.8f, Vector4(0.0f, 0.0f, 1.0f, 1.0f), 0.05f);
	Particle* particle1 = new Particle(anchorP1 + Vector3D(0.0f, -restingL1, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 1.0f, physx::PxSphereGeometry(0.5f), Vector4(0.0f, 1.0f, 1.0f, 1.0f), 0.0, 1.5f);

	setups.push_back({ anchoredSpring1, particle1 });
}

void Scene3::update(double dt) {
	const bool applyingImpulse = impulseTimer > 0.0f;

	if (impulseTimer > 0.0f) {
		impulseTimer -= static_cast<float>(dt);
	}

	for (auto& s : setups) {
		Particle* p = s.particle;

		p->clearForces();

		gravity->updateForce(p);

		if (applyingImpulse) {
			p->addForce(Vector3D(100.0f, -15.0f, 0.0f));
		}

		s.anchoredSpring->updateForce(p);

		switch (integrationMethod) {
			case 0:
				p->integrateEuler(dt);
				break;
			case 1:
				p->integrateSemiImplicitEuler(dt);
				break;
			default:
				p->integrateVerlet(dt);
				break;
		}
	}
}

void Scene3::keyPress(unsigned char key, const physx::PxTransform& camera) {
	PX_UNUSED(camera);

	if (setups.empty()) {
		return;
	}

	auto& anchoredS = setups[0];

	switch (key) {
		case '+':
			anchoredS.anchoredSpring->setK(anchoredS.anchoredSpring->getK() * 1.5f);
			break;

		case '-':
			anchoredS.anchoredSpring->setK(anchoredS.anchoredSpring->getK() / 1.5f);
			break;

		case 'i':
		case 'I':
			impulseTimer = 0.1f;
			break;

		case 'm':
		case 'M':
			integrationMethod = (integrationMethod + 1) % 3;
			break;

		case 'x':
		case 'X':
			anchoredS.anchoredSpring->setDampingRatio(anchoredS.anchoredSpring->getDampingRatio() + 0.01f);
			break;

		case 'z':
		case 'Z':
			anchoredS.anchoredSpring->setDampingRatio(anchoredS.anchoredSpring->getDampingRatio() - 0.01f);
			break;

		default:
			break;
	}
}

void Scene3::cleanup() {
	for (auto& s : setups) {
		delete s.anchoredSpring;
		delete s.particle;
	}
	setups.clear();

	delete gravity;
	gravity = nullptr;

	impulseTimer = 0.0f;
	integrationMethod = 2;

	Scene::cleanup();
}