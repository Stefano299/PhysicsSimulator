//
// Created by stefano on 9/6/24.
//

#include <iostream>

#include "glad/glad.h"
#include "System.h"

System::System(): camera(glm::vec3(0.0f, 0.0f, 0.0f), 0.1f, 0.12f) {
    initWindow();
    initOpenGL();
    //Prima di fare chiamate binding di opengl devo inizializzare il contesto della finestra
    sphereContainer = std::unique_ptr<SphereContainer>(new SphereContainer);
    sphereContainer->addSphere(glm::vec3(0.0f, 0.0f, -5.0f));
}

void System::handleEvents()  {
    if((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
        window.close();
    }
    else if(event.type == sf::Event::Resized){
        glViewport(0, 0, event.size.width, event.size.height);
        //TODO aggiorna projection matrix
    }
    camera.handleRotation(event);
    camera.handleCursorLock(event, window);
}


void System::handleInput() {
    camera.handleMovement();
}

void System::update() {
    camera.reset(window);
}

void System::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sphereContainer->draw(camera.getView(), camera.getProjection());
    window.display();
}

void System::run() {
    while(window.isOpen()){
        while(window.pollEvent(event)){
            handleEvents();
        }
        handleInput();
        update();
        render();
    }
}

void System::initWindow() {
    sf::ContextSettings settings;
    settings.attributeFlags = sf::ContextSettings::Core;
    settings.majorVersion = 3;
    settings.minorVersion = 3;
    settings.depthBits = 24;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Physics Simulator", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    window.setActive(true);
}

void System::initOpenGL() const {
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(sf::Context::getFunction))){
        std::cerr << "Errore nella inizializzione di GLAD" << std::endl;
    }
    glClearColor(0.6f, 0.8f, 0.9f, 1.0f);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
}

