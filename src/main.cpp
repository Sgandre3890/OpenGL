#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.h"
#include "shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    if (Window::initializeWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL") != 0)
        return -1;

    // Load shaders from files
    Shader shader("include/shaders/vertShader.glsl", "include/shaders/fragShader.glsl");

    // Vertex data
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
         0.5f, -0.5f, 0.0f, // right
         0.0f,  0.5f, 0.0f  // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Main loop: handles rendering and event processing until the window is closed
    while (!glfwWindowShouldClose(Window::window))
    {
        // Process user input
        Window::processInput(Window::window);

        // Clear the screen and set the draw color
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shader program
        Shader shader("vertex.glsl", "fragment.glsl");
        shader.use();  // probably defined in shader.h
        shader.setFloat("someUniform", 1.0f);
        shader.setVec4("color", 1.0f, 0.5f, 0.2f, 1.0f);


        // Bind the vertex array object and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the front and back buffers and poll for events
        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    Window::terminateWindow();
    return 0;
}
