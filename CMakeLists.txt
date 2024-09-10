cmake_minimum_required(VERSION 3.28)
project(PhysicsSimulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(PhysicsSimulator sources/main.cpp
        sources/System.cpp
        headers/System.h
        headers/constants.h
        include/glad.c
        sources/Sphere.cpp
        headers/Sphere.h
        sources/Shader.cpp
        sources/SphereContainer.cpp
        headers/SphereContainer.h
        sources/Camera.cpp
        headers/stb_image.h
        sources/stb_image.cpp
        sources/helper.cpp
        sources/Platform.cpp
        headers/Platform.h
        sources/SkyBox.cpp
        headers/gameTime.h
        sources/PhysicsEngine.cpp
        headers/PhysicsEngine.h
        sources/CollisionSystem.cpp
        headers/CollisionSystem.h
        sources/Emitter.cpp
        headers/Emitter.h
        sources/SidePlatform.cpp
        headers/SidePlatform.h
        sources/Container.cpp
        headers/Container.h
        sources/CollisionSections.cpp
        headers/CollisionSections.h
)
        
target_include_directories(PhysicsSimulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PhysicsSimulator GL sfml-graphics sfml-window sfml-system)
