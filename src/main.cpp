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
    if (Window::initializeWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL") != 0)
        return -1;

    // Load shaders from files
    Shader shader("../shaders/shader.vs", "../shaders/shader.fs");

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

    // Render loop
    while (!glfwWindowShouldClose(Window::window))
    {
        Window::processInput(Window::window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        shader.setVec4("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    Window::terminateWindow();
    return 0;
}
