cmake_minimum_required(VERSION 3.28)
project(PhysicsSimulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(PhysicsSimulator main.cpp
        System.cpp
        System.h
        constants.h
        include/glad.c
)
        
target_include_directories(PhysicsSimulator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(PhysicsSimulator GL sfml-graphics sfml-window sfml-system)
