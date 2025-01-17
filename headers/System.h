//
// Created by stefano on 9/6/24.
//

#ifndef PHYSICSSIMULATION_SYSTEM_H
#define PHYSICSSIMULATION_SYSTEM_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "constants.h"
#include "Camera.h"
#include "Emitter.h"

class Container;
class Platform;
class SkyBox;
class PhysicsEngine;
class System {
private:
    void handleEvents();
    void handleInput();
    void update();
    void render();
    void initWindow();
    void initOpenGL() const;
    void showFPS() const;
    sf::RenderWindow window;
    sf::Event event;
    Camera camera;
    std::shared_ptr<Emitter> emitter;
    std::unique_ptr<SkyBox> skyBox;
    std::shared_ptr<Container> container;
    std::unique_ptr<PhysicsEngine> physicsEngine;
    sf::Clock clock;
public:
    System();
    void run();
    ~System();
};


#endif //PHYSICSSIMULATION_SYSTEM_H
