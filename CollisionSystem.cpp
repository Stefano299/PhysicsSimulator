//
// Created by stefano on 9/7/24.
//

#include "CollisionSystem.h"
#include "Sphere.h"
#include "Platform.h"

bool CollisionSystem::spherePlatform(const Sphere& sphere, const Platform& platform){
    float sphereRadius = sphere.getSize().y;
    float topSideY = platform.getPosition().y+0.5f*platform.getSize().y; //L'altezza della faccia superiore della piattaforma inferiore
    float dTime = 1.0f/60; //Secondi tra un frame e l'altro
    glm::vec3 dPos = sphere.getVelocity()*dTime;
    glm::vec3 sphereFuturePos = sphere.getPos()+dPos;

    return(sphereFuturePos.y-sphereRadius <= topSideY);
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
    if(glm::length(normal) <= sphere1Radius + sphere2Radius){
        normal = glm::normalize(normal);
        return true;
    }else{
        normal = glm::vec3(0.0f);
        return false;
    }
}
