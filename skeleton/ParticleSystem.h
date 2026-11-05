#pragma once
#include "Particle.h"
#include "ForceGenerator.h"
#include <random>
#include <algorithm>
class ParticleSystem
{
public:
	struct Config {
        Vector3D origin; // Origen del sistema de partículas
        float spawnRate; // Partículas por segundo
        float posVariance; // Varianza de la posición inicial
		float maxPosOffset; // Desplazamiento máximo de la posición inicial
        Vector3D meanVelocity; // Velocidad media inicial
        float velVariance; // Varianza de la velocidad
		float maxVelMagnitude; // Magnitud máxima de la velocidad inicial

        double maxLifetime; // Tiempo de vida
        float radius; // Tamaño de la partícula
        Vector4 color; // Color
        float damping; // Damping
		float mass; // Masa

        float maxDistanceSq; // Distancia máxima al origen
	};

	ParticleSystem(const Config& config);
	~ParticleSystem();

    void tick(double dt);
	void update(double dt);
    Vector3D getOrigin() const noexcept;
    void setOrigin(const Vector3D& newOrigin) noexcept;
    void setActive(bool active) noexcept;
    bool isActive() const noexcept;
	size_t getParticleCount() const noexcept;
    void addForceGenerator(ForceGenerator* fg);
    void removeForceGenerator(ForceGenerator* fg);
	void cleanup() noexcept;

private:
    bool active = true;

    Config config;
    std::vector<Particle*> particles;

    std::mt19937 rng;
    std::normal_distribution<float> velDistribution;
    std::normal_distribution<float> posDistribution;
    std::uniform_real_distribution<float> lifeTimeDistribution;

    double spawnAccumulator = 0.0;

    std::vector<ForceGenerator*> forceGenerators;

    void generateParticle();
};

