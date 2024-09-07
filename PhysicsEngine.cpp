//
// Created by stefano on 9/7/24.
//

#include "PhysicsEngine.h"
#include "SphereContainer.h"
#include "Platform.h"
#include "CollisionSystem.h"

PhysicsEngine::PhysicsEngine(std::shared_ptr<SphereContainer> sphereContainer, std::shared_ptr<Platform> platform) {
    this->sphereContainer = sphereContainer;
    this->platform = platform;
}

void PhysicsEngine::gravity() const {
    for(auto& it: const_cast<std::vector<Sphere>&>(sphereContainer->getSpheres())){
        float dt = 1.f/60; //Secondi tra un frame e l'altro
        float dv = -G*dt; // a = dv/dt
        glm::vec3 velOffset = glm::vec3(0.0f, dv, 0.0f);
        glm::vec3 newVel = it.getVelocity()+velOffset;
        handlePlatformsCollisions(it, newVel);
        handleSpheresCollisions(it);
    }
}

void PhysicsEngine::handlePlatformsCollisions(Sphere &it, const glm::vec3 &newVel) const {
    if(!CollisionSystem::spherePlatform(it, *platform)) { //Controlla la posizione futura
        it.setVelocity(newVel);
    }else
    {
        glm::vec3 reflectedVel = glm::reflect(it.getVelocity(), glm::vec3(0.0f, 1.0f, 0.0f));
        it.setVelocity(reflectedVel); //Non voglio aumenti la velocità nel momento in cui torna su
    }
}

void PhysicsEngine::handleSpheresCollisions(Sphere& it1) const {
    glm::vec3 normal;
    for (auto &it2: const_cast<std::vector<Sphere> &>(sphereContainer->getSpheres())) {
        if(it1 != it2 && CollisionSystem::sphereSphere(it1, it2, normal)){ //Ricordo che normal va da it1 a it2
            glm::vec3 sphere2ReflectedVel = glm::reflect(it2.getVelocity(), normal);
            glm::vec3 sphere1ReflectedVel = glm::reflect(it1.getVelocity(), -normal);
            it1.setVelocity(sphere1ReflectedVel);
            it2.setVelocity(sphere2ReflectedVel);
        }
    }
}


void PhysicsEngine::update() {
    gravity();
}

