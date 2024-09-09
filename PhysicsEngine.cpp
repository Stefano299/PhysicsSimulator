//
// Created by stefano on 9/7/24.
//

#include "PhysicsEngine.h"
#include "SphereContainer.h"
#include "Container.h"
#include "CollisionSystem.h"
#include "Emitter.h"
#include "CollisionSections.h"

PhysicsEngine::PhysicsEngine(std::shared_ptr<Emitter> emitter, std::shared_ptr<Container> container) {
    this->emitter = emitter;
    this->container = container;
    collisionSections = std::unique_ptr<CollisionSections>(new CollisionSections(5, 5, 5, *container));
}

void PhysicsEngine::gravity() const {
    for (auto &it: const_cast<std::vector<Sphere> &>(emitter->getSpheres())) {
        float dt = 1.f / 60; //Secondi tra un frame e l'altro
        float dv = -G * dt; // a = dv/dt
        glm::vec3 velOffset = glm::vec3(0.0f, dv, 0.0f);
        glm::vec3 newVel = it.getVelocity() + velOffset;
        handleContainerCollisions(it, newVel);
        collisionSections->setSphereSection(&it);
        //handleSpheresCollisions(it);
    }
}

void PhysicsEngine::handleContainerCollisions(Sphere &it, const glm::vec3 &newVel) const {
    glm::vec3 normal; //Vettore normale alla collisione
    if(!CollisionSystem::sphereContainer(it, *container, normal)) { //Controlla la posizione futura
        it.setVelocity(newVel);
    }else
    {
        glm::vec3 reflectedVel = glm::reflect(it.getVelocity(), normal);
        it.setVelocity(reflectedVel); //Non voglio aumenti la velocità nel momento in cui torna su
    }
}

void PhysicsEngine::handleSpheresCollisions(Sphere& it1) const {
    glm::vec3 normal;
    for (auto &it2: const_cast<std::vector<Sphere> &>(emitter->getSpheres())) {
        if(it1 != it2 && CollisionSystem::sphereSphere(it1, it2, normal)){ //Ricordo che normal va da it1 a it2
            glm::vec3 sphere2ReflectedVel = glm::reflect(it2.getVelocity(), normal);
            glm::vec3 sphere1ReflectedVel = glm::reflect(it1.getVelocity(), -normal);
            it1.setVelocity(sphere1ReflectedVel);
            it2.setVelocity(sphere2ReflectedVel);
        }
    }
}

void PhysicsEngine::handleSpheresCollisionsOPT() const {
    for(const auto& itVec: collisionSections->getSections()) {
        for(const auto& it1: itVec) {
            glm::vec3 normal;
            for (const auto &it2: itVec) {
                if (it1 != it2 && CollisionSystem::sphereSphere(*it1, *it2, normal)) { //Ricordo che normal va da it1 a it2
                    glm::vec3 sphere2ReflectedVel = glm::reflect(it2->getVelocity(), normal);
                    glm::vec3 sphere1ReflectedVel = glm::reflect(it1->getVelocity(), -normal);
                    it1->setVelocity(sphere1ReflectedVel);
                    it2->setVelocity(sphere2ReflectedVel);
                }
            }
        }
    }
}




void PhysicsEngine::update() {
    collisionSections->clearSections();
    gravity();
    handleSpheresCollisionsOPT();
}

