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

const int width = 1920;
const int height = 1080;

int main(){

    // Opening the window part ---------------------------------------------------------
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

    //----------------------------------------------------------------------------------
    // Define vertices for our object
    GLfloat vertices[] = { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
            -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
            0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
            0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
            -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
            0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

            -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
            0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
            0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

            0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
            0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
            0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

            0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
            -0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
            0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
    };

    GLuint indices[] = {

            0, 1, 2, // Bottom side
            0, 2, 3, // Bottom side
            4, 6, 5, // Left side
            7, 9, 8, // Non-facing side
            10, 12, 11, // Right side
            13, 15, 14 // Facing side
    };

    GLfloat lightVertices[] = {
            -0.1f, -0.1f,  0.1f,
            -0.1f, -0.1f, -0.1f,
            0.1f, -0.1f, -0.1f,
            0.1f, -0.1f,  0.1f,
            -0.1f,  0.1f,  0.1f,
            -0.1f,  0.1f, -0.1f,
            0.1f,  0.1f, -0.1f,
            0.1f,  0.1f,  0.1f
    };

    GLuint lightIndices[] =
            {
                    0, 1, 2,
                    0, 2, 3,
                    0, 4, 7,
                    0, 7, 3,
                    3, 7, 6,
                    3, 6, 2,
                    2, 6, 5,
                    2, 5, 1,
                    1, 5, 4,
                    1, 4, 0,
                    4, 5, 6,
                    4, 6, 7
            };

    //----------------------------------------------------------------------------------
    // link shaders to shader program
    Shader shaderProgram("../resources/default.vert", "../resources/default.frag");
    // VAO, VBO & EBO
    VAO VAO_1;
    VAO_1.Bind();

    VBO VBO_1(vertices, sizeof(vertices));
    EBO EBO_1(indices, sizeof(indices));

    VAO_1.LinkAttrib(VBO_1, 0, 3, GL_FLOAT, 11*sizeof(float ), (void*)0);
    VAO_1.LinkAttrib(VBO_1, 1, 3, GL_FLOAT, 11*sizeof(float ), (void*)(3*sizeof(float)));
    VAO_1.LinkAttrib(VBO_1, 2, 2, GL_FLOAT, 11*sizeof(float ), (void*)(6*sizeof(float)));
    VAO_1.LinkAttrib(VBO_1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));

    VAO_1.Unbind();
    VBO_1.Unbind();
    EBO_1.Unbind();

    GLint scaleID = glGetUniformLocation(shaderProgram.ID, "scale");

    // Light Source --------------------------------------------------------------------

    Shader lightShader("../resources/light.vert", "../resources/light.frag");
    VAO lightVAO;
    lightVAO.Bind();

    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightIndices, sizeof(lightIndices));

    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3*sizeof(float), (void*)0);

    lightVAO.Unbind();
    lightVBO.Unbind();
    lightEBO.Unbind();

    // --------------------------------------------------------------------------------
    // light source & object-----------------------------------------------------------

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3 (0.0f, 1.3f, 0.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    glm::vec3 objPos = glm::vec3 (0.0f, 0.0f, 0.0f);
    glm::mat4 objModel = glm::mat4 (1.0f);
    objModel = glm::translate(objModel, objPos);

    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    shaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objModel));
    glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    // Texture ------------------------------------------------------------------------
    Texture objTex("../resources/Textures/wall.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    objTex.texUnit(shaderProgram, "tex0", 0);

    // Fix for the Texture glitch
    glEnable(GL_DEPTH_TEST);

    // --------------------------------------------------------------------------------
    // Camera--------------------------------------------------------------------------
    // create the Camera object
    Camera camera(width, height, glm::vec3(0.0f, 0.5f, 2.5f));
    float fov = 85.0f;
    // Scrolling Callback (todo: to be implemented)
    glfwSetScrollCallback(window, Camera::ScrollCallback);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera Handling
        camera.KeyInputs(window);
        camera.MouseInputs(window);
        camera.UpdateMatrix(fov, 0.1f, 100.0f);

        shaderProgram.Activate();
        // Exports the camera Position to the Fragment Shader for specular lighting
        camera.Matrix(shaderProgram, "camMatrix");

        glUniform1f(scaleID, 0.5);
        objTex.Bind();
        VAO_1.Bind();

        // Specular lighting
        glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.camPosition.x, camera.camPosition.y, camera.camPosition.z);

        // while drawing, we must provide opengl hint on how to render (line, points,
        // or fill with triangles) these points, this is called "primitives".
        glDrawElements(GL_TRIANGLES, sizeof(indices)/ sizeof(int), GL_UNSIGNED_INT, 0);

        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/ sizeof(int), GL_UNSIGNED_INT, 0);

        // Swap back buffer with the front buffer
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
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    lightShader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}