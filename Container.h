//
// Created by stefano on 9/9/24.
//

#ifndef PHYSICSSIMULATOR_CONTAINER_H
#define PHYSICSSIMULATOR_CONTAINER_H

#include <memory>

#include "SidePlatform.h"
#include "Platform.h"

class Container {
private:
    void initFaces();
    std::unique_ptr<SidePlatform> frontFace;
    std::unique_ptr<SidePlatform>  backFace;
    std::unique_ptr<SidePlatform>  leftFace;
    std::unique_ptr<SidePlatform>  rightFace;
    std::unique_ptr<Platform> bottomFace;
    glm::vec3 position;
    glm::vec3 size;
public:
    Container(const glm::vec3 &position, const glm::vec3 &size);
    void draw(const glm::mat4& view, const glm::mat4& projection) const;
    const glm::vec3& getBottomPos() const;
    const glm::vec3& getLeftPos() const;
    const glm::vec3& getRightPos() const;
    const glm::vec3& getFrontPos() const;
    const glm::vec3& getBackPos() const;
    const glm::vec3& getSize() const;
};


#endif //PHYSICSSIMULATOR_CONTAINER_H
