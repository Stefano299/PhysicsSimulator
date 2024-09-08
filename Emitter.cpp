//
// Created by stefano on 9/7/24.
//

#include <iostream>

#include "Emitter.h"
#include "gameTime.h"
#include "constants.h"

Emitter::Emitter(const glm::vec3& position, float speed) {
    this->position = position;
    this->speed = speed;
    direction = glm::normalize(glm::vec3(-1.0f, 4.0f, 0.0f));
    rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Emitter::emitSpheres() {
    static float lastTIme = gameTime;
    float dt = gameTime-lastTIme;
    if(dt >= speed){
        lastTIme = gameTime;
        glm::vec3 velocity = direction*4.0f;
        sphereContainer.addSphere(position, velocity);
        direction = glm::vec3(glm::vec4(direction, 1.0f)*rotationMatrix);
    }
}

void Emitter::updateSpheres() {
    sphereContainer.moveSpheres();
}

const std::vector<Sphere> &Emitter::getSpheres() const {
    return sphereContainer.getSpheres();
}

void Emitter::drawSpheres(const glm::mat4 &view, const glm::mat4 &projection) {
    sphereContainer.draw(view, projection);
}

void Emitter::createCylinder(const glm::vec3& pos, float radius, float height) {
    //Aggiungo 0.5f per evitare conflitti
    for(int i = 0; i < (int)(height/(SPHERE_RADIUS*2)); i++){
        glm::vec3 centerPos = pos - glm::vec3(0.0, (double)i*(SPHERE_RADIUS*2+0.01), 0.0);
        float R = radius;
        while(R > SPHERE_RADIUS){
            float angleOffset = glm::degrees(2*asin((double)SPHERE_RADIUS/R))+0.5f;
            glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angleOffset), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::vec3 dir = glm::vec3(-1.0, 0.0, 0.0);
            for(int j = 0; j < (int)(360.0/angleOffset); j++){
                sphereContainer.addSphere(dir*R+centerPos, glm::vec3(0.0f));
                dir = glm::normalize(glm::vec3(rotMatrix*glm::vec4(dir, 1.0f)));
            }
            R -= SPHERE_RADIUS*2;
        }
    }
}

