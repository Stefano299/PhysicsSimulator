//
// Created by stefano on 9/9/24.
//

#include "Container.h"
#include "constants.h"

Container::Container(const glm::vec3 &position, const glm::vec3 &size) {
    this->position = position;
    this->size = size*2.0f; //I cubi sono in mezzo metro ma io voglio considerare i metri
    initFaces();
}

void Container::draw(const glm::mat4 &view, const glm::mat4 &projection) const {
    bottomFace->draw(view, projection);
    frontFace->draw(view, projection);
    leftFace->draw(view, projection);
    rightFace->draw(view, projection);
    backFace->draw(view, projection);
}

void Container::initFaces() {
    float offset = FACE_THICKNESS/2; //Per farle incastrare bene...
    bottomFace = std::unique_ptr<Platform>(new Platform(position, glm::vec3(size.x, FACE_THICKNESS, size.z)));
    glm::vec3 frontFacePos = glm::vec3(position.x, position.y + size.y / 2-offset, position.z + size.z / 2);
    glm::vec3 backFacePos = glm::vec3(position.x, position.y + size.y / 2-offset, position.z - size.z / 2);
    glm::vec3 leftFacePos = glm::vec3(position.x - size.x / 2, position.y + size.y / 2-offset, position.z);
    glm::vec3 rightFacePos = glm::vec3(position.x + size.x / 2, position.y + size.y / 2-offset, position.z);
    //Spesso uguale a 0 perchè ho notato che si vedono meglio come quadrati non parallelepipedi "poco spessi"
    frontFace = std::unique_ptr<SidePlatform>(new SidePlatform(frontFacePos, glm::vec3(size.x, size.y, 0)));
    backFace = std::unique_ptr<SidePlatform>(new SidePlatform(backFacePos, glm::vec3(size.x, size.y, 0)));
    leftFace = std::unique_ptr<SidePlatform>(new SidePlatform(leftFacePos, glm::vec3(0, size.y, size.z)));
    rightFace = std::unique_ptr<SidePlatform>(new SidePlatform(rightFacePos, glm::vec3(0, size.y, size.z)));
}

const glm::vec3 &Container::getBottomPos() const {
    return bottomFace->getPosition();
}

const glm::vec3 &Container::getLeftPos() const {
    return leftFace->getPosition();
}

const glm::vec3 &Container::getRightPos() const {
    return rightFace->getPosition();
}

const glm::vec3 &Container::getFrontPos() const {
    return frontFace->getPosition();
}

const glm::vec3 &Container::getBackPos() const {
    return backFace->getPosition();
}

const glm::vec3 &Container::getSize() const {
    return size;
}
