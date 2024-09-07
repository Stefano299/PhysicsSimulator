//
// Created by stefano on 9/6/24.
//

#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "System.h"
#include "gameTime.h"
#include "PhysicsEngine.h"
#include "SkyBox.h"
#include "Platform.h"
#include "SphereContainer.h"

float gameTime = 0;

System::System(): camera(glm::vec3(0.0f, 1.0f, 0.0f), 0.1f, 0.12f) {
    clock.restart();
    initWindow();
    initOpenGL();
    //Prima di fare chiamate binding di opengl devo inizializzare il contesto della finestra
    sphereContainer = std::unique_ptr<SphereContainer>(new SphereContainer);
    sphereContainer->addSphere(glm::vec3(0.0f, 1.25f, -5.0f));
    sphereContainer->addSphere(glm::vec3(0.05f, 2.0f, -5.0f));
    platform = std::make_shared<Platform>(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(15.0f, 0.5f, 15.0f));
    skyBox = std::make_shared<SkyBox>();
    physicsEngine = std::make_shared<PhysicsEngine>(sphereContainer, platform);
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
    gameTime = clock.getElapsedTime().asSeconds();
    physicsEngine->update();
    sphereContainer->moveSpheres(); //Si muovono secondo il loro attributo velocità
    camera.reset(window);
}

void System::render() {
    glm::mat4 view = camera.getView();
    glm::mat4 projection = camera.getProjection();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    skyBox->draw(projection, glm::mat4(glm::mat3(view)));
    sphereContainer->draw(view, projection);
    platform->draw(view, projection);
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


