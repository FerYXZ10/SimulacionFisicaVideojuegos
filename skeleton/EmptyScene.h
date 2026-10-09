#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transforms.push_back(physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f)));

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItems.push_back(new RenderItem(shape, &m_transforms.back(), Vector4(1.0f, 0.0f, 0.0f, 1.0f)));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transforms.back().p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }
    }
};