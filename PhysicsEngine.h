//
// Created by stefano on 9/7/24.
//

#ifndef PHYSICSSIMULATOR_PHYSICSENGINE_H
#define PHYSICSSIMULATOR_PHYSICSENGINE_H

#include<memory>

#include "gameTime.h"
#include "constants.h"

class SphereContainer;
class Platform;
class PhysicsEngine {
private:
    void gravity() const;
    std::shared_ptr<SphereContainer> sphereContainer;
    std::shared_ptr<Platform> platform;
public:
    PhysicsEngine(std::shared_ptr<SphereContainer> sphereContainer, std::shared_ptr<Platform> platform);
    void update();
};


#endif //PHYSICSSIMULATOR_PHYSICSENGINE_H
