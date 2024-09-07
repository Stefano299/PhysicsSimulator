//
// Created by stefano on 9/6/24.
//

#ifndef PHYSICSSIMULATOR_SPHERE_H
#define PHYSICSSIMULATOR_SPHERE_H

#include <vector>
#include <glm/glm.hpp>

class Shader;
class Sphere {
private:
    static void initVertices();
    static void initBuffers();
    static float* vertexPos;
    static unsigned int VAO;
    static unsigned int VBO;
    glm::vec3 position;
    glm::mat4 model;
public:
    Sphere() = default;
    explicit Sphere(const glm::vec3& pos);
    static unsigned int getVAO();
    const glm::mat4& getModel() const;
    static void initData();
    ~Sphere() = default; //TODO toglielo e metterci una funzione statica chiamata alla fine di system, in quanto l'array è statica
};


#endif //PHYSICSSIMULATOR_SPHERE_H
