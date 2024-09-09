cmake_minimum_required(VERSION 3.28)
project(PhysicsSimulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(PhysicsSimulator main.cpp
        System.cpp
        System.h
        constants.h
        include/glad.c
        Sphere.cpp
        Sphere.h
        Shader.cpp
        SphereContainer.cpp
        SphereContainer.h
        Camera.cpp
        stb_image.h
        stb_image.cpp
        helper.cpp
        Platform.cpp
        Platform.h
        SkyBox.cpp
        gameTime.h
        PhysicsEngine.cpp
        PhysicsEngine.h
        CollisionSystem.cpp
        CollisionSystem.h
        Emitter.cpp
        Emitter.h
        SidePlatform.cpp
        SidePlatform.h
        Container.cpp
        Container.h
        CollisionSections.cpp
        CollisionSections.h
)
        
target_include_directories(PhysicsSimulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PhysicsSimulator GL sfml-graphics sfml-window sfml-system)
