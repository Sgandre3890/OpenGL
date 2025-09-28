#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.h"
#include "shader.h"

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    if (Window::initializeWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL") != 0)
        return -1;

    // Load shaders from files
    Shader shader("include/shaders/vertex.glsl", "include/shaders/fragment.glsl");

    // Vertex data
    GLfloat vertices[] = {
    // positions       // colors
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };


    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set the vertex attribute pointer for the position data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Set the vertex attribute pointer for the color data
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Set the vertex attribute pointer for the normal data
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Unbind the vertex array object so that other vertex array objects can be used
    glBindVertexArray(0);

    // Unbind the vertex buffer object so that other vertex buffer objects can be used
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Main loop: handles rendering and event processing until the window is closed
    while (!glfwWindowShouldClose(Window::window))
    {
        // Process user input
        Window::processInput(Window::window);

        // Clear the screen and set the draw color
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        // Bind the vertex array object and draw the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap the front and back buffers and poll for events
        glfwSwapBuffers(Window::window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
    
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    Window::terminateWindow();
    return 0;
}
