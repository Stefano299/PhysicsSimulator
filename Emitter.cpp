//
// Created by stefano on 9/7/24.
//

#include <iostream>

#include "Emitter.h"
#include "gameTime.h"

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

