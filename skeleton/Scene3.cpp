#include "Scene3.h"

Scene3::~Scene3() {
	Scene3::cleanup();
}

void Scene3::init() {
	if (!setups.empty() || !pairs.empty()) {
		return;
	}

	gravity = new GravityForceGenerator(Vector3D(0.0f, -9.81f, 0.0f));

	wind = new WindForceGenerator(Vector3D(-10.0f, 0.0f, 0.0f), 0.5f, 0.0f, Vector3D(7.5f, 8.0f, 0.0f), 1000.0f);

	const Vector3D anchorP1 = Vector3D(-5.0f, 5.0f, 0.0f);
	constexpr float restingL1 = 5.0f;

	AnchoredSpringForceGenerator* anchoredSpring1 = new AnchoredSpringForceGenerator(
		10.0f,
		restingL1,
		anchorP1,
		0.8f,
		Vector4(0.0f, 0.0f, 1.0f, 1.0f),
		0.05f
	);

	Particle* particle1 = new Particle(
		anchorP1 + Vector3D(0.0f, -restingL1, 0.0f),
		Vector3D(0.0f, 0.0f, 0.0f),
		1.0f,
		physx::PxSphereGeometry(0.5f),
		Vector4(0.0f, 1.0f, 1.0f, 1.0f),
		0.0,
		1.5f
	);

	setups.push_back({ anchoredSpring1, particle1 });

	constexpr float k2 = 20.0f;
	constexpr float restingL2 = 6.0f;

	Particle* particleA = new Particle(
		Vector3D(5.0f, 8.0f, 0.0f),
		Vector3D(0.0f, 0.0f, 0.0f),
		1.0f,
		physx::PxSphereGeometry(1.0f),
		Vector4(1.0f, 0.5f, 0.5f, 1.0f),
		0.0,
		1.0f
	);

	Particle* particleB = new Particle(
		Vector3D(10.0f, 8.0f, 0.0f),
		Vector3D(0.0f, 0.0f, 0.0f),
		1.0f,
		physx::PxSphereGeometry(1.0f),
		Vector4(0.5f, 0.5f, 1.0f, 1.0f),
		0.0,
		3.0f
	);

	SpringForceGenerator* springA = new SpringForceGenerator(k2, restingL2, particleB);
	SpringForceGenerator* springB = new SpringForceGenerator(k2, restingL2, particleA);

	SpringForceGenerator* bandA = new ElasticBandForceGenerator(k2, restingL2, particleB);
	SpringForceGenerator* bandB = new ElasticBandForceGenerator(k2, restingL2, particleA);

	pairs.push_back({ particleA, particleB, springA, springB, bandA, bandB, false });

	updateDisplayText();
}

void Scene3::update(double dt) {
	const bool applyingSetupImpulse = impulseTimerSetup > 0.0f;

	if (impulseTimerSetup > 0.0f) {
		impulseTimerSetup -= static_cast<float>(dt);
	}

	const bool applyingPairImpulse = impulseTimerPair > 0.0f;

	if (impulseTimerPair > 0.0f) {
		impulseTimerPair -= static_cast<float>(dt);
	}

	for (auto& s : setups) {
		Particle* p = s.particle;

		p->clearForces();

		gravity->updateForce(p);

		if (applyingSetupImpulse) {
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
			case 2:
				p->integrateVerlet(dt);
				break;
			default:
				break;
		}
	}

	for (auto& pair : pairs) {
		Particle* pA = pair.particleA;
		Particle* pB = pair.particleB;

		pA->clearForces();
		pB->clearForces();

		if (windActive) {
			wind->updateForce(pA);
			wind->updateForce(pB);
		}

		if (applyingPairImpulse) {
			pA->addForce(Vector3D(100.0f, 0.0f, 0.0f));
		}

		SpringForceGenerator* fgA = pair.useBand ? pair.bandFromA : pair.springFromA;
		SpringForceGenerator* fgB = pair.useBand ? pair.bandFromB : pair.springFromB;

		fgA->updateForce(pA);
		fgB->updateForce(pB);

		switch (integrationMethod) {
			case 0:
				pA->integrateEuler(dt);
				pB->integrateEuler(dt);
				break;
			case 1:
				pA->integrateSemiImplicitEuler(dt);
				pB->integrateSemiImplicitEuler(dt);
				break;
			case 2:
				pA->integrateVerlet(dt);
				pB->integrateVerlet(dt);
				break;
			default:
				break;
		}
	}
}

void Scene3::keyPress(unsigned char key, const physx::PxTransform& camera) {
	PX_UNUSED(camera);

	if (!setups.empty()) {
		auto& anchoredS = setups.at(0);

		switch (key) {
			case '+':
				anchoredS.anchoredSpring->setK(anchoredS.anchoredSpring->getK() * 1.5f);
				break;

			case '-':
				anchoredS.anchoredSpring->setK(anchoredS.anchoredSpring->getK() / 1.5f);
				break;

			case 'x':
			case 'X':
				anchoredS.anchoredSpring->setDampingRatio(anchoredS.anchoredSpring->getDampingRatio() + 0.05f);
				break;

			case 'z':
			case 'Z':
				anchoredS.anchoredSpring->setDampingRatio(anchoredS.anchoredSpring->getDampingRatio() - 0.05f);
				break;

			case 'i':
			case 'I':
				impulseTimerSetup = 0.1f;
				break;

			default:
				break;
		}
	}

	if (!pairs.empty()) {
		auto& pair = pairs.at(0);

		switch (key) {
			case 'l':
			case 'L': {
				const float nK = pair.springFromA->getK() * 1.5f;
				pair.springFromA->setK(nK);
				pair.springFromB->setK(nK);
				pair.bandFromA->setK(nK);
				pair.bandFromB->setK(nK);
				break;
			}

			case 'k':
			case 'K': {
				const float nK = pair.springFromA->getK() / 1.5f;
				pair.springFromA->setK(nK);
				pair.springFromB->setK(nK);
				pair.bandFromA->setK(nK);
				pair.bandFromB->setK(nK);
				break;
			}

			case 'u':
			case 'U': {
				const float nD = pair.springFromA->getDampingRatio() + 0.05f;
				pair.springFromA->setDampingRatio(nD);
				pair.springFromB->setDampingRatio(nD);
				pair.bandFromA->setDampingRatio(nD);
				pair.bandFromB->setDampingRatio(nD);
				break;
			}

			case 'y':
			case 'Y': {
				const float nD = std::max<float>(0.0f, pair.springFromA->getDampingRatio() - 0.05f);
				pair.springFromA->setDampingRatio(nD);
				pair.springFromB->setDampingRatio(nD);
				pair.bandFromA->setDampingRatio(nD);
				pair.bandFromB->setDampingRatio(nD);
				break;
			}

			case 'b':
			case 'B':
				pair.useBand = !pair.useBand;
				updateDisplayText();
				break;

			case 'o':
			case 'O':
				impulseTimerPair = 0.1f;
				break;

			case 't':
			case 'T':
				windActive = !windActive;
				updateDisplayText();
				break;

			case 'n':
			case 'N': {
				if (wind) {
					windDirIndex = (windDirIndex + 1) % 4;
					windActive = true;
					switch (windDirIndex) {
					case 0:
						wind->setWindVel(Vector3D(-10.0f, 0.0f, 0.0f));
						break;
					case 1:
						wind->setWindVel(Vector3D(10.0f, 0.0f, 0.0f));
						break;
					case 2:
						wind->setWindVel(Vector3D(0.0f, 0.0f, -10.0f));
						break;
					case 3:
						wind->setWindVel(Vector3D(0.0f, 0.0f, 10.0f));
						break;
					default:
						break;
					}
					updateDisplayText();
				}
				break;
			}

			default:
				break;
		}
	}

	if (key == 'm' || key == 'M') {
		integrationMethod = (integrationMethod + 1) % 3;
		updateDisplayText();
	}
}

void Scene3::cleanup() {
	for (auto& s : setups) {
		delete s.anchoredSpring;
		delete s.particle;
	}
	setups.clear();

	for (auto& pair : pairs) {
		delete pair.particleA;
		delete pair.particleB;
		delete pair.springFromA;
		delete pair.springFromB;
		delete pair.bandFromA;
		delete pair.bandFromB;
	}
	pairs.clear();

	delete gravity;
	gravity = nullptr;

	delete wind;
	wind = nullptr;

	impulseTimerSetup = 0.0f;
	impulseTimerPair = 0.0f;
	integrationMethod = 2;
	windActive = false;
	windDirIndex = 0;

	Scene::cleanup();
}

void Scene3::updateDisplayText() {
	std::string text = "Scene 3 | ";

	if (!pairs.empty()) {
		text += (pairs.at(0).useBand ? "Goma" : "Muelle");
	}
	else {
		text += "---";
	}

	switch (integrationMethod) {
		case 0:
			text += " | Euler";
			break;
		case 1:
			text += " | Semi-Implicit Euler";
			break;
		case 2:
			text += " | Verlet";
			break;
		default:
			break;
	}

	text += " | Wind: ";
	if (!windActive) {
		text += "OFF";
	}
	else {
		switch (windDirIndex) {
			case 0:
				text += "-X";
				break;
			case 1:
				text += "+X";
				break;
			case 2:
				text += "-Z";
				break;
			case 3:
				text += "+Z";
				break;
			default:
				break;
		}
	}

	display_text = text;
}