//
// Created by stefano on 9/7/24.
//

#ifndef PHYSICSSIMULATOR_COLLISIONSYSTEM_H
#define PHYSICSSIMULATOR_COLLISIONSYSTEM_H

#include <glm/glm.hpp>

class Sphere;
class Platform;
namespace CollisionSystem {
    const glm::vec3& spherePlatform(const Sphere& sphere, const Platform& platform);
};


#endif //PHYSICSSIMULATOR_COLLISIONSYSTEM_H
