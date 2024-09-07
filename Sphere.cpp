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

Sphere::Sphere(const glm::vec3 &pos) {
    position = pos;
    model = glm::translate(glm::mat4(1.0), pos);
}

void Sphere::initVertices() {
    vertexPos = new float[11664];
    for(int i = 0; i < 18; i++){
        float y1 = cos(glm::radians(i*10.0f));
        float y2 = cos(glm::radians((i+1)*10.0f));
        float coeff1 = sin(glm::radians((i)*10.0f)); //Coefficenti da moltiplicare per le coordinate, come con il cos del pitch
        float coeff2 = sin(glm::radians((i+1)*10.0f));
        for(int j = 0; j < 36; j++){
            float x1 = sin(glm::radians(j*10.0f));
            float z1 = cos(glm::radians(j*10.0f));
            float x2 = sin(glm::radians((j+1)*10.0f));
            float z2 = cos(glm::radians((j+1)*10.0f));

            vertexPos[i*18*36+j*18] = x1*coeff1;
            vertexPos[i*18*36+j*18+1] = y1;
            vertexPos[i*18*36+j*18+2] = z1*coeff1;

            vertexPos[i*18*36+j*18+3] = x2*coeff2;
            vertexPos[i*18*36+j*18+4] = y2;
            vertexPos[i*18*36+j*18+5] = z2*coeff2;

            vertexPos[i*18*36+j*18+6] = x1*coeff2;
            vertexPos[i*18*36+j*18+7] = y2;
            vertexPos[i*18*36+j*18+8] = z1*coeff2;

            vertexPos[i*18*36+j*18+9] = x2*coeff1;
            vertexPos[i*18*36+j*18+10] = y1;
            vertexPos[i*18*36+j*18+11] = z2*coeff1;

            vertexPos[i*18*36+j*18+12] =x2*coeff2;
            vertexPos[i*18*36+j*18+13] = y2;
            vertexPos[i*18*36+j*18+14] = z2*coeff2;

            vertexPos[i*18*36+j*18+15] = x1*coeff1;
            vertexPos[i*18*36+j*18+16] = y1;
            vertexPos[i*18*36+j*18+17] = z1*coeff1;
        }
    }
}

void Sphere::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*11664, vertexPos, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);

    glEnableVertexAttribArray(0);
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
