//
// Created by stefano on 9/7/24.
//

#ifndef PHYSICSSIMULATOR_COLLISIONSYSTEM_H
#define PHYSICSSIMULATOR_COLLISIONSYSTEM_H

#include "glm/glm.hpp"

class Sphere;
class Container;
namespace CollisionSystem {
    bool sphereContainer(const Sphere& sphere, const Container& container, glm::vec3 &normal);
    //Il terzo argomento restituisce il vettore normale dello scontro
    bool sphereSphere(const Sphere& sphere1, const Sphere& sphere2, glm::vec3& normal);
};


#endif //PHYSICSSIMULATOR_COLLISIONSYSTEM_H
