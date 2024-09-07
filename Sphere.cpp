//
// Created by stefano on 9/6/24.
//

#include <iostream>

#include "Sphere.h"
#include "glad/glad.h"
#include "glm/ext/matrix_transform.hpp"

unsigned int Sphere::VAO = 0;
unsigned int Sphere::VBO = 0;
float* Sphere::vertexPos = nullptr;
std::vector<float> Sphere::vertexNormals;

Sphere::Sphere(const glm::vec3 &pos) {
    position = pos;
    model = glm::translate(glm::mat4(1.0), pos);
}

void Sphere::initVertices() {
    vertexPos = new float[186624];

    for (int i = 0; i < 72; i++) {
        float y1 = cos(glm::radians(i * 2.5f));
        float y2 = cos(glm::radians((i + 1) * 2.5f));
        float coeff1 = sin(glm::radians(i * 2.5f));
        float coeff2 = sin(glm::radians((i + 1) * 2.5f));

        for (int j = 0; j < 144; j++) {
            float x1 = sin(glm::radians(j * 2.5f));
            float z1 = cos(glm::radians(j * 2.5f));
            float x2 = sin(glm::radians((j + 1) * 2.5f));
            float z2 = cos(glm::radians((j + 1) * 2.5f));

            int offset = (i * 144 * 18) + (j * 18);

            // Primo triangolo
            vertexPos[offset] = x1 * coeff1;
            vertexPos[offset + 1] = y1;
            vertexPos[offset + 2] = z1 * coeff1;

            vertexPos[offset + 3] = x2 * coeff2;
            vertexPos[offset + 4] = y2;
            vertexPos[offset + 5] = z2 * coeff2;

            vertexPos[offset + 6] = x1 * coeff2;
            vertexPos[offset + 7] = y2;
            vertexPos[offset + 8] = z1 * coeff2;

            glm::vec3 vec1 = glm::vec3(vertexPos[offset]-vertexPos[offset + 6], vertexPos[offset + 1]-vertexPos[offset + 7], vertexPos[offset + 2]-vertexPos[offset + 8]);
            glm::vec3 vec2 = glm::vec3(vertexPos[offset]-vertexPos[offset + 3], vertexPos[offset + 1]-vertexPos[offset + 4], vertexPos[offset + 2]-vertexPos[offset + 5]);
            addNormals(vec1, vec2);

            // Secondo triangolo
            vertexPos[offset + 9] = x2 * coeff1;
            vertexPos[offset + 10] = y1;
            vertexPos[offset + 11] = z2 * coeff1;

            vertexPos[offset + 12] = x2 * coeff2;
            vertexPos[offset + 13] = y2;
            vertexPos[offset + 14] = z2 * coeff2;

            vertexPos[offset + 15] = x1 * coeff1;
            vertexPos[offset + 16] = y1;
            vertexPos[offset + 17] = z1 * coeff1;

            vec1 = glm::vec3(vertexPos[offset + 12]-vertexPos[offset + 9], vertexPos[offset + 13]-vertexPos[offset + 10], vertexPos[offset + 14] - vertexPos[offset + 11]);
            vec2 = glm::vec3(vertexPos[offset + 12]-vertexPos[offset + 15], vertexPos[offset + 13]-vertexPos[offset + 16], vertexPos[offset + 14] - vertexPos[offset + 17]);
            addNormals(vec1, vec2);
        }
    }
}

void Sphere::addNormals(const glm::vec3 &vec1, const glm::vec3 &vec2) {
    glm::vec3 normal = glm::normalize(glm::cross(vec1, vec2));
    vertexNormals.push_back(normal.x);
    vertexNormals.push_back(normal.y);
    vertexNormals.push_back(normal.z);

    vertexNormals.push_back(normal.x);
    vertexNormals.push_back(normal.y);
    vertexNormals.push_back(normal.z);

    vertexNormals.push_back(normal.x);
    vertexNormals.push_back(normal.y);
    vertexNormals.push_back(normal.z);
}

void Sphere::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*186624*2, nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float)*186624, vertexPos);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(float)*186624, sizeof(float)*186624, vertexNormals.data());
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)(sizeof(float)*186624));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

unsigned int Sphere::getVAO() {
    return VAO;
}

const glm::mat4 &Sphere::getModel() const {
    return model;
}

void Sphere::initData() {
    initVertices();
    initBuffers();
}


