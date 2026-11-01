#pragma once
#include "Particle.h"
#include <random>
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
        Vector3D gravity; // Gravedad
        float damping; // Damping

        float maxDistanceSq; // Distancia máxima al origen
	};

	ParticleSystem(const Config& config);
	~ParticleSystem();

	void update(double dt);
    Vector3D getOrigin() const noexcept;
    void setOrigin(const Vector3D& newOrigin) noexcept;
    void setActive(bool active) noexcept;
    bool isActive() const noexcept;
	void cleanup() noexcept;

private:
    bool m_isActive = true;

    Config m_config;
    std::vector<Particle*> m_particles;

    std::mt19937 m_rng;
    std::normal_distribution<float> m_velDistribution;
    std::normal_distribution<float> m_posDistribution;

    double m_spawnAccumulator = 0.0;

    void generateParticle();
};

