//
// Created by stefano on 9/7/24.
//

#include "../headers/CollisionSystem.h"
#include "../headers/Sphere.h"
#include "../headers/Container.h"
#include "../headers/constants.h"

bool CollisionSystem::sphereContainer(const Sphere& sphere, const Container& container, glm::vec3 &normal){
    float sphereRadius = sphere.getSize().y;
    float dTime = 1.0f/60; //Secondi tra un frame e l'altro
    glm::vec3 dPos = sphere.getVelocity()*dTime;
    glm::vec3 sphereFuturePos = sphere.getPos()+dPos;
    float offset = FACE_THICKNESS/2;
    //Controllo le varie facce del  cubo
    bool collision = false;
    if (sphereFuturePos.y - sphereRadius <= container.getBottomPos().y + offset) {
        normal = glm::vec3(0.0f, 1.0f, 0.0f);
        collision = true;
    }  if (sphereFuturePos.z + sphereRadius >= container.getFrontPos().z - offset) {
        normal = glm::vec3(0.0f, 0.0f, -1.0f);
        collision = true;
    }  if (sphereFuturePos.z - sphereRadius <= container.getBackPos().z + offset) {
        normal = glm::vec3(0.0f, 0.0f, 1.0f);
        collision = true;
    }  if (sphereFuturePos.x - sphereRadius <= container.getLeftPos().x + offset) {
        normal = glm::vec3(1.0f, 0.0f, 0.0f);
        collision = true;
    }  if (sphereFuturePos.x + sphereRadius >= container.getRightPos().x - offset) {
        normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        collision = true;
    }
    //Anche se non la ho creata esplicitamente, considero come se ci fosse una faccia superiore al cubo
    if (sphereFuturePos.y + sphereRadius >= container.getFrontPos().y +container.getSize().y/2) {
        normal = glm::vec3(0.0f, -1.0f, 0.0f);
        collision = true;
    }
    if (!collision){
        normal = glm::vec3(0.0f);
    }
    return collision;
}

bool CollisionSystem::sphereSphere(const Sphere& sphere1, const Sphere& sphere2, glm::vec3& normal){
    float sphere1Radius = sphere1.getSize().y;
    float sphere2Radius = sphere2.getSize().y;
    float dTime = 1.0f/60;
    //Anche con le sfere controllo le loro posizioni future
    glm::vec3 dPos1 = sphere1.getVelocity()*dTime;
    glm::vec3 sphere1FuturePos = sphere1.getPos()+dPos1;

    glm::vec3 dPos2 = sphere2.getVelocity()*dTime;
    glm::vec3 sphere2FuturePos = sphere2.getPos()+dPos2;

    normal = sphere2FuturePos-sphere1FuturePos;
    bool collision = false;
    if(glm::length(normal) <= sphere1Radius + sphere2Radius){
        normal = glm::normalize(normal);
        collision = true;
    }else{
        normal = glm::vec3(0.0f);
        collision = false;
    }
    return collision;
}
