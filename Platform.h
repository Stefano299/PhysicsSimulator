//
// Created by stefano on 9/7/24.
//

#ifndef PHYSICSSIMULATOR_PLATFORM_H
#define PHYSICSSIMULATOR_PLATFORM_H

#include "glm/glm.hpp"
#include "Shader.h"

class Platform {
private:
    void initVertices();
    void initBuffers();
    void initShader();
    unsigned int VAO;
    unsigned int VBO;
    float vertices[216];
    glm::vec3 position;
    glm::vec3 size;
    glm::mat4 model;
    Shader shader;
public:
    Platform(const glm::vec3& pos, const glm::vec3& size);
    void draw(const glm::mat4& view, const glm::mat4& projection) const;
};


#endif //PHYSICSSIMULATOR_PLATFORM_H
