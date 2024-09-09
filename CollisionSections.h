//
// Created by stefano on 9/9/24.
//

#ifndef PHYSICSSIMULATOR_COLLISIONSECTIONS_H
#define PHYSICSSIMULATOR_COLLISIONSECTIONS_H

#include <vector>

#include "glm/glm.hpp"

class Container;
class Sphere;
class CollisionSections {
private:
    void initVector();
    int width;
    int height;
    int depth;
    glm::vec3 containerSize;
    glm::vec3 cubeSize;  //Le dimensioni dei cubi sezione in cui ci sono gli indirizzi delle sfere
    glm::vec3 containerPos;
    std::vector<std::vector<Sphere*>> sections;
public:
    CollisionSections(int width, int height, int depth, const Container& container);
    void setSphereSection(Sphere* sphere);
    const std::vector<std::vector<Sphere*>> getSections() const;
};


#endif //PHYSICSSIMULATOR_COLLISIONSECTIONS_H
