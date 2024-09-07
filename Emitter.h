//
// Created by stefano on 9/7/24.
//

#ifndef PHYSICSSIMULATOR_EMITTER_H
#define PHYSICSSIMULATOR_EMITTER_H

#include <memory>

#include "SphereContainer.h"

class Emitter {
private:
    SphereContainer sphereContainer;
    glm::vec3 position;
    glm::vec3 direction;
    glm::mat4 rotationMatrix;
    float speed;
public:
    Emitter(const glm::vec3& position, float speed);
    void emitSpheres();
    void updateSpheres();
    const std::vector<Sphere>& getSpheres() const;
    void drawSpheres(const glm::mat4& view, const glm::mat4& projection);
};


#endif //PHYSICSSIMULATOR_EMITTER_H
