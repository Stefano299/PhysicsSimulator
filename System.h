//
// Created by stefano on 9/6/24.
//

#ifndef PHYSICSSIMULATION_SYSTEM_H
#define PHYSICSSIMULATION_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "constants.h"
#include "SphereContainer.h"
#include "Camera.h"

class System {
private:
    void handleEvents();
    void handleInput();
    void update();
    void render();
    void initWindow();
    void initOpenGL() const;
    sf::RenderWindow window;
    sf::Event event;
    Camera camera;
    std::unique_ptr<SphereContainer> sphereContainer;
public:
    System();
    void run();
};


#endif //PHYSICSSIMULATION_SYSTEM_H
