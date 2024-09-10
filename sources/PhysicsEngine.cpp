//
// Created by stefano on 9/7/24.
//

#include <thread>
#include "../headers/PhysicsEngine.h"
#include "../headers/SphereContainer.h"
#include "../headers/Container.h"
#include "../headers/CollisionSystem.h"
#include "../headers/Emitter.h"
#include "../headers/CollisionSections.h"

PhysicsEngine::PhysicsEngine(std::shared_ptr<Emitter> emitter, std::shared_ptr<Container> container) {
    this->emitter = emitter;
    this->container = container;
    collisionSections = std::unique_ptr<CollisionSections>(new CollisionSections(6, 6, 6, *container));
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
    glm::vec3 newNormal;
    /*Può succedere che anche con la nuova vel la sfera rimanga "incastrata" nella faccia con cui ha fatto collisione
    a causa delle collisioni con le altre sfere. Per risolvere il problema controllo se, anche dopo con la nuova velocità
    collide con la stessa faccia. In questo caso imposto una velocità con direzione ortogonale alla faccia e la muovo
    per essere sicuro esca dalla "zona critica"*/
    if(CollisionSystem::sphereContainer(it, *container, newNormal) && normal == newNormal){
        glm::vec3 correctedVel = newNormal*glm::length(newVel);
        it.setVelocity(correctedVel);
        it.move();
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
    const auto& sections = collisionSections->getSections();
    int nThreads = 16; //Quelli della mia cpu
    int nSections = collisionSections->getSections().size();
    int nSectionsPerThread = nSections/nThreads; //Ogni thread ha un numero di sezione da svolgere


    //Funzione lambda chiamata dal thread
    auto threadFunc = [&](int start, int end){
        auto startIt = std::next(sections.begin(), start);
        auto endIt = std::next(sections.begin(), end);
        for(auto itVec = startIt; itVec != endIt; itVec++) {
            for(const auto& it1: *itVec) {
                glm::vec3 normal;
                for (const auto &it2: *itVec) {
                    if (it1 != it2 && CollisionSystem::sphereSphere(*it1, *it2, normal)) { //Ricordo che normal va da it1 a it2
                        glm::vec3 sphere2ReflectedVel = glm::reflect(it2->getVelocity(), normal);
                        glm::vec3 sphere1ReflectedVel = glm::reflect(it1->getVelocity(), -normal);
                        it1->setVelocity(sphere1ReflectedVel);
                        it2->setVelocity(sphere2ReflectedVel);
                    }
                }
            }
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(nThreads);

    for(int i = 0; i < nThreads; i++){
        if(i == nThreads-1){  //La divisione non è perfetta.. l'ultimo ha più lavoro
            threads.emplace_back(threadFunc, i*nSectionsPerThread, nSections);
            break;
        }
        threads.emplace_back(threadFunc, i*nSectionsPerThread, (i+1)*nSectionsPerThread);
    }

    for(auto& thread: threads){
        if(thread.joinable()){
            thread.join();
        }
    }
    threads.clear();
}




void PhysicsEngine::update() {
    collisionSections->clearSections();
    gravity();
    handleSpheresCollisionsOPT();
}

