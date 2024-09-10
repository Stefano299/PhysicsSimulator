//
// Created by stefano on 9/6/24.
//

#ifndef PHYSICSSIMULATOR_SPHERECONTAINER_H
#define PHYSICSSIMULATOR_SPHERECONTAINER_H

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Sphere.h"

class SphereContainer {
private:
    void setAttribPointers();
    void initShader();
    void updateModels();
    std::vector<Sphere> spheres;
    std::vector<glm::mat4> models;
    Shader shader;
    unsigned int instancesVBO;
public:
    SphereContainer();
    void draw(const glm::mat4& view, const glm::mat4& projection);
    void addSphere(const glm::vec3& pos, const glm::vec3& velocity);
    void moveSpheres();
    const std::vector<Sphere>& getSpheres() const;
    ~SphereContainer();
};


#endif //PHYSICSSIMULATOR_SPHERECONTAINER_H
