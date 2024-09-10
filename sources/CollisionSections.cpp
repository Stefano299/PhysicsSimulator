//
// Created by stefano on 9/9/24.
//

#include "../headers/CollisionSections.h"
#include "../headers/Sphere.h"
#include "../headers/Container.h"

CollisionSections::CollisionSections(int width, int height, int depth, const Container& container) {
    this->width = width;
    this->height = height;
    this->depth = depth;
    containerSize = container.getSize();
    containerPos =container.getFrontPos() - glm::vec3(containerSize.x/2, containerSize.y/2, 0.0f);
    cubeSize = glm::vec3(containerSize.x/(float)width, containerSize.y/(float)height, containerSize.y/(float)depth);
    initVector();
}

void CollisionSections::initVector() {
    sections.reserve(width * height * depth);
    for(int i = 0; i < width*height*depth; i++){
        sections.emplace_back();  //Inserisco dentro i vettori di indirizzi di sfere
    }
}

void CollisionSections::setSphereSection(Sphere *sphere) {
    //Devo avere la posizione relativa al container
    glm::vec3 offset = glm::vec3(1000.0f);
    //LO FACCIO PER AVERE TUTTE COORDINATE POSITIVE, O I CALCOLI VERREBERO STRANI
    glm::vec3 containerPosCorrected = containerPos + offset;
    glm::vec3 spherePos = sphere->getPos()-glm::vec3(containerPosCorrected.x, containerPosCorrected.y, 0.0f);
    spherePos += offset;

    spherePos.z = containerPosCorrected.z - spherePos.z;
    int x = spherePos.x/cubeSize.x;
    int y = spherePos.y/cubeSize.y;
    int z = spherePos.z/cubeSize.z;
    //Per prevedere segmentation faults
    //Ci sarebbero delle correzioni da fare, ma evito di spenderci tempo in tanto diminuisco di molto poco la precisione
    if(x >= 5) x=4;
    if(y >= 5 ) y = 4;
    if (z >= 5) z = 4;
    if(x < 0) x = 0;
    if(y < 0) y = 0;
    if(z < 0) z = 0;
    sections[x*height*depth+y*depth+z].push_back(sphere);
}

const std::vector<std::vector<Sphere *>> CollisionSections::getSections() const {
    return sections;
}

void CollisionSections::clearSections() {
    //Pulisco tutti i vettori prima di riempirli ancora
    for(auto& it: sections) {
        it.clear();
    }
}
