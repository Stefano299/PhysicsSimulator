//
// Created by stefano on 9/7/24.
//

#include "PhysicsEngine.h"
#include "SphereContainer.h"
#include "Platform.h"

PhysicsEngine::PhysicsEngine(std::shared_ptr<SphereContainer> sphereContainer, std::shared_ptr<Platform> platform) {
    this->sphereContainer = sphereContainer;
    this->platform = platform;
}

void PhysicsEngine::gravity() const {
    for(auto& it: const_cast<std::vector<Sphere>&>(sphereContainer->getSpheres())){
        float dt = 1.f/60; //Secondi tra un frame e l'altro
        float dv = -G*dt; // a = dv/dt
        glm::vec3 velOffset = glm::vec3(0.0f, dv, 0.0f);
        it.setVelocity(it.getVelocity()+velOffset);
    }
}

void PhysicsEngine::update() {
    gravity();
}
