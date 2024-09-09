//
// Created by stefano on 9/8/24.
//

#ifndef PHYSICSSIMULATOR_SIDEPLATFORM_H
#define PHYSICSSIMULATOR_SIDEPLATFORM_H

#include "glm/glm.hpp"
#include "Shader.h"

class SidePlatform {
private:
    void initBuffers();
    void initShader();
    static unsigned int VAO;
    static unsigned int VBO;
    static float vertices[72];
    glm::vec3 position;
    glm::vec3 size;
    glm::mat4 model;
    static Shader shader;
public:
    SidePlatform(const glm::vec3 &position, const glm::vec3 &size);
    void draw(const glm::mat4& view, const glm::mat4& projection) const;
};


#endif //PHYSICSSIMULATOR_SIDEPLATFORM_H
