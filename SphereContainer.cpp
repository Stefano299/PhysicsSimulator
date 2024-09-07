//
// Created by stefano on 9/6/24.
//

#include "SphereContainer.h"

SphereContainer::SphereContainer() {
    glGenBuffers(1, &instancesVBO);
    initShader();
    Sphere::initData(); //CONTANDO CI SIA UN SOLO CONTAINER
}

void SphereContainer::draw(const glm::mat4 &view, const glm::mat4 &projection) {
    shader.useProgram();
    shader.changeUniform4M("view", view);
    shader.changeUniform4M("projection", projection);
    glBindVertexArray(Sphere::getVAO());
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3888, spheres.size());
}


void SphereContainer::addSphere(const glm::vec3 &pos) {
    Sphere sphere(pos);
    spheres.push_back(sphere);
    models.push_back(sphere.getModel());
    setAttribPointers();
}

void SphereContainer::setAttribPointers() {
    std::size_t vec4Size = sizeof(glm::vec4);
    unsigned int nSpheres = spheres.size();
    glBindVertexArray(Sphere::getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, instancesVBO);
    glBufferData(GL_ARRAY_BUFFER, nSpheres*vec4Size*4, models.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)vec4Size);
    glEnableVertexAttribArray(3);
    glVertexAttribDivisor(3, 1);

    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)(vec4Size*2));
    glEnableVertexAttribArray(4);
    glVertexAttribDivisor(4, 1);

    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, vec4Size*4, (void*)(vec4Size*3));
    glEnableVertexAttribArray(5);
    glVertexAttribDivisor(5, 1);
}

void SphereContainer::initShader() {
    shader.loadVertex("../Sphere.vert");
    shader.loadFragment("../Sphere.frag");
    shader.createProgram();
}



