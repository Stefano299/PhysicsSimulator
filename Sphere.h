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
    static void addNormals(const glm::vec3& vec1, const glm::vec3& vec2);
    static void initVertices();
    static void initBuffers();
    static float* vertexPos;
    static std::vector<float> vertexNormals;
    static unsigned int VAO;
    static unsigned int VBO;
    glm::vec3 velocity;
    glm::vec3 position;
    glm::mat4 model;
    float mass;
public:
    Sphere() = default;
    void move();
    explicit Sphere(const glm::vec3& pos);
    static unsigned int getVAO();
    const glm::mat4& getModel() const;
    static void initData();
    const glm::vec3& getPos() const;
    float getMass() const;
    void setVelocity(const glm::vec3& vel);
    const glm::vec3& getVelocity() const;
    ~Sphere() = default; //TODO toglielo e metterci una funzione statica chiamata alla fine di system, in quanto l'array è statica
};


#endif //PHYSICSSIMULATOR_SPHERE_H
