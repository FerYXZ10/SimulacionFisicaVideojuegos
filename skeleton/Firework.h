#pragma once
#include "ParticleSystem.h"
#include "GravityForceGenerator.h"
#include <utility>
#include <cmath>
class Firework
{
public:
    struct Config {
        Vector3D origin; // Origen del que sale el cohete
        float posVariance; // Varianza de la posición inicial
        float maxPosOffset; // Desplazamiento máximo de la posición inicial
        Vector3D meanVelocity; // Velocidad media inicial
		float velVariance; // Varianza de la velocidad
        float maxVelMagnitude; // Magnitud máxima de la velocidad inicial
        float radius; // Tamaño de la partícula
        Vector4 color; // Color del cohete
        float damping; // Damping
		float mass; // Masa del cohete
		std::vector<Vector4> explosionColors; // Paleta de colores de las partículas de la explosión
	};

    Firework(const Config& conf, const ParticleSystem::Config& explConfig);
    ~Firework();

    void update(double dt);
    bool isFinished() const;

    void addForceGenerator(ForceGenerator* fg);

private:
    Config config;
    std::mt19937 rng;
    std::normal_distribution<float> velDistribution;
    std::normal_distribution<float> posDistribution;
    Particle* rocket;
    ParticleSystem::Config explosionConfig;
    std::vector<std::pair<ParticleSystem*, float>> explosions;
    std::vector<ForceGenerator*> forceGenerators;
};

