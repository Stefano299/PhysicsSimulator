//
// Created by stefano on 9/6/24.
//

#ifndef PHYSICSSIMULATION_SYSTEM_H
#define PHYSICSSIMULATION_SYSTEM_H

#include <SFML/Graphics.hpp>

#include "constants.h"

class System {
private:
    void handleEvents();
    void handleInput() const;
    void update() const;
    void render();
    void initWindow();
    void initOpenGL() const;
    sf::RenderWindow window;
    sf::Event event;
public:
    System();
    void run();
};


#endif //PHYSICSSIMULATION_SYSTEM_H
