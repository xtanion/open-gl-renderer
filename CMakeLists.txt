cmake_minimum_required(VERSION 3.22)
project(pyramid)

set(CMAKE_CXX_STANDARD 14)

add_executable(pyramid
        src/main.cpp
        src/glad.c
        headers/shaderClass.h
        src/shaderClass.cpp
        headers/VBO.h src/VBO.cpp headers/EBO.h src/EBO.cpp headers/VAO.h src/VAO.cpp include/stb/stb_image.h src/stb.cpp src/Texture.cpp headers/Texture.h headers/Camera.h src/Camera.cpp)

include_directories(GL)
target_link_libraries(pyramid GL glfw dl)