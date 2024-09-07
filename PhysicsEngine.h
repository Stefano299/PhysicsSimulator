//
// Created by stefano on 9/7/24.
//

#ifndef PHYSICSSIMULATOR_PHYSICSENGINE_H
#define PHYSICSSIMULATOR_PHYSICSENGINE_H

#include<memory>

#include "gameTime.h"
#include "constants.h"
#include "Sphere.h"

class Emitter;
class Platform;
class PhysicsEngine {
private:
    void gravity() const;
    void handlePlatformsCollisions(Sphere &it, const glm::vec3& newVel) const;
    void handleSpheresCollisions(Sphere &it1) const;
    std::shared_ptr<Emitter> emitter;
    std::shared_ptr<Platform> platform;
public:
    PhysicsEngine(std::shared_ptr<Emitter> sphereContainer, std::shared_ptr<Platform> platform);
    void update();

};


#endif //PHYSICSSIMULATOR_PHYSICSENGINE_H
