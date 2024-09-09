//
// Created by stefano on 9/8/24.
//

#include "SidePlatform.h"

float SidePlatform::vertices[72] ={         // Linee della base
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,  // V0 -> V1
        0.5f, -0.5f, -0.5f,   0.5f,  0.5f, -0.5f,  // V1 -> V2
        0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,  // V2 -> V3
        -0.5f,  0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,  // V3 -> V0

// Linee della parte superiore (z = 0.5f)
        -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,  // V4 -> V5
        0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,  // V5 -> V6
        0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,  // V6 -> V7
        -0.5f,  0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,  // V7 -> V4

// Linee verticali (collegano la base alla parte superiore)
        -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,  // V0 -> V4
        0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,  // V1 -> V5
        0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,  // V2 -> V6
        -0.5f,  0.5f, -0.5f,  -0.5f,  0.5f,  0.5f   // V3 -> V7
};

Shader SidePlatform::shader;
unsigned int SidePlatform::VBO = 0;
unsigned int SidePlatform::VAO = 0;

SidePlatform::SidePlatform(const glm::vec3 &position, const glm::vec3 &size) {
    this->position = position;
    this->size = size;
    model = glm::translate(glm::mat4(1.0f), position);
    model =  glm::scale(model, size);
    //model = glm::rotate()
    initBuffers();
    initShader();
    shader.useProgram();
    shader.changeUniform4M("model", model);
}

void SidePlatform::draw(const glm::mat4 &view, const glm::mat4 &projection) const {
    shader.useProgram();
    shader.changeUniform4M("model", model); //Sennò se ne ho di più ne disegna solo una
    shader.changeUniform4M("view", view);
    shader.changeUniform4M("projection", projection);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 24);
}


void SidePlatform::initBuffers() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0);
}

void SidePlatform::initShader() {
    shader.loadVertex("../SidePlatform.vert");
    shader.loadFragment("../SidePlatform.frag");
    shader.createProgram();
}

const glm::vec3& SidePlatform::getPosition() const {
    return position;
}

