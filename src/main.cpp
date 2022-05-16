#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../headers/shaderClass.h"
#include "../headers/VAO.h"
#include "../headers/VBO.h"
#include "../headers/EBO.h"

// Textures
//#include "../include/stb/stb_image.h"
#include "../headers/Texture.h"
// glm for matrix math
#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"
#include "../include/glm/gtc/type_ptr.hpp"
// Camera
#include "../headers/Camera.h"

const int width = 960;
const int height = 540;

int main(){


    GLfloat vertices[] = {
            //  vertices        color values   tex coord
            -0.5, -0.5,  0.5,  1.0, 0.0, 0.0,  1.0/4.0, 1.0/3.0, //
             0.5, -0.5,  0.5,  0.0, 1.0, 0.0,  2.0/4.0, 1.0/3.0, // Front Face
             0.5,  0.5,  0.5,  0.0, 0.0, 1.0,  2.0/4.0, 2.0/3.0, //
            -0.5,  0.5,  0.5,  1.0, 1.0, 1.0,  1.0/4.0, 2.0/3.0, //

            -0.5, -0.5, -0.5,  1.0, 0.0, 0.0,  4.0/4.0, 1.0/3.0, //
             0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  3.0/4.0, 1.0/3.0, // Back Face
             0.5,  0.5, -0.5,  0.0, 0.0, 1.0,  3.0/4.0, 2.0/3.0, //
            -0.5,  0.5, -0.5,  1.0, 1.0, 1.0,  4.0/4.0, 2.0/3.0, //

            0.5, -0.5, -0.5,  1.0, 0.0, 0.0,  3.0/4.0, 1.0/3.0, //
            0.5,  0.5, -0.5,  0.0, 1.0, 0.0,  3.0/4.0, 2.0/3.0, // Right Face
            0.5,  0.5,  0.5,  0.0, 0.0, 1.0,  2.0/4.0, 2.0/3.0, //
            0.5, -0.5,  0.5,  1.0, 1.0, 1.0,  2.0/4.0, 1.0/3.0, //

            -0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  0.0/4.0, 2.0/3.0, //
            -0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  0.0/4.0, 1.0/3.0, // Left Face
            -0.5, -0.5,  0.5,  0.0, 0.0, 1.0,  1.0/4.0, 1.0/3.0, //
            -0.5,  0.5,  0.5,  1.0, 1.0, 1.0,  1.0/4.0, 2.0/3.0, //

            -0.5, -0.5, -0.5,  1.0, 0.0, 0.0,  1.0/4.0, 0.0, //
             0.5, -0.5, -0.5,  0.0, 1.0, 0.0,  2.0/4.0, 0.0, // Bottom Face
             0.5, -0.5,  0.5,  0.0, 0.0, 1.0,  2.0/4.0, 1.0/3.0, //
            -0.5, -0.5,  0.5,  1.0, 1.0, 1.0,  1.0/4.0, 1.0/3.0, //

             0.5,  0.5, -0.5,  1.0, 0.0, 0.0,  1.0/4.0, 2.0/3.0, //
            -0.5,  0.5, -0.5,  0.0, 1.0, 0.0,  1.0/4.0, 3.0/3.0, // Top face
            -0.5,  0.5,  0.5,  0.0, 0.0, 1.0,  2.0/4.0, 3.0/3.0, //
             0.5,  0.5,  0.5,  1.0, 1.0, 1.0,  2.0/4.0, 2.0/3.0  //
    };

    GLuint indices[] = {
            0,  1,  2,  2,  3,  0,
            4,  5,  6,  6,  7,  4,
            8,  9, 10, 10, 11,  8,
            12, 13, 14, 14, 15, 12,
            16, 17, 18, 18, 19, 16,
            20, 21, 22, 22, 23, 20
    };


    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(width, height, "square", nullptr, nullptr);
    if(window==nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    // link shaders to shader program
    Shader shaderProgram("../resources/default.vert", "../resources/default.frag");

    // VAO, VBO & EBO
    VAO VAO_1;
    VAO_1.Bind();

    VBO VBO_1(vertices, sizeof(vertices));
    EBO EBO_1(indices, sizeof(indices));

    VAO_1.LinkAttrib(VBO_1, 0, 3, GL_FLOAT, 8*sizeof(float ), (void*)0);
    VAO_1.LinkAttrib(VBO_1, 1, 3, GL_FLOAT, 8*sizeof(float ), (void*)(3*sizeof(float)));
    VAO_1.LinkAttrib(VBO_1, 2, 2, GL_FLOAT, 8*sizeof(float ), (void*)(6*sizeof(float)));

    VAO_1.Unbind();
    VBO_1.Unbind();
    EBO_1.Unbind();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // Swap the back buffer with the front buffer
    glfwSwapBuffers(window);

//    GLuint  uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Loading the image
    Texture objTex("../resources/Textures/skybox.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    objTex.texUnit(shaderProgram, "tex0", 0);

    // Fix for the Texture glitch
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    // create the camera  object
    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 5.0f));
    float fov = 45.0f;
    glfwSetScrollCallback(window, Camera::ScrollCallback);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        camera.KeyInputs(window);
        camera.MouseInputs(window);
        camera.Matrix(fov, 0.1f, 100.0f, shaderProgram, "camMatrix");

        objTex.Bind();

        VAO_1.Bind();

        // while drawing, we must provide opengl hint on how to render (line, points,
        // or fill with triangles) these points, this is called "primitives".
        // They are of following types: GL_POINT, GL_TRIANGLE, GL_LINE_STRIP
        glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the buffer objects
    VAO_1.Delete();
    VBO_1.Delete();
    EBO_1.Delete();
    objTex.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}