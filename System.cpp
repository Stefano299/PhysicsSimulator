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
#include "Container.h"
#include "CollisionSections.h"

float gameTime = 0;

System::System(): camera(glm::vec3(0.0f, 7.f, 27.0f), 0.5f, 0.12f) {
    clock.restart();
    initWindow();
    initOpenGL();
    emitter = std::make_shared<Emitter>(glm::vec3(0.0f, 2.0f, -5.0f), 0.01f, 15);
    emitter->setMaxSpheres(1500);
    //emitter->createCylinder(glm::vec3(0.0f, 7.0f, 0.0f), 0.4, 1);
    skyBox = std::unique_ptr<SkyBox>(new SkyBox);
    container = std::make_shared<Container>(glm::vec3(0.0, 0.0, 0.0), glm::vec3(7.0f, 7.0f, 7.f));
    physicsEngine = std::unique_ptr<PhysicsEngine>(new PhysicsEngine(emitter, container));
}

void System::handleEvents()  {
    if((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
        window.close();
    }
    else if(event.type == sf::Event::Resized){
        glViewport(0, 0, event.size.width, event.size.height);
        camera.updateProjection(event.size.width, event.size.height);
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
    emitter->emitSpheres();
    emitter->updateSpheres(); //Si muovono secondo il loro attributo velocità
    camera.reset(window);
    showFPS();
    std::cout << emitter->getSpheresCount() << std::endl;
}

void System::render() {
    glm::mat4 view = camera.getView();
    glm::mat4 projection = camera.getProjection();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    skyBox->draw(projection, glm::mat4(glm::mat3(view)));
    emitter->drawSpheres(view, projection);
    container->draw(view, projection);
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
    glLineWidth(10.0f);
}

void System::showFPS() const {
    static sf::Clock FPSclock;
    float time;
    time = FPSclock.getElapsedTime().asSeconds();
    std::cout << 1.f/time << std::endl;
    FPSclock.restart();
}

System::~System() {
    Sphere::clear();
}


