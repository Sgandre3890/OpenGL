#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "window.h"
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    if (Window::initializeWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL") != 0)
        return -1;

    // Load shaders from files
    Shader shader("include/shaders/vertex.glsl", "include/shaders/fragment.glsl");

    // Vertex data
    // Each vertex: position (3), color (3), texcoord (2), normal (3)
    // stride = 11 floats
    GLfloat vertices[] = {
        // position           // color      // tex    // normal
        // Base
        -0.5f, 0.0f,  0.5f,   1,1,1,    0,0,   0,-1,0,  // 0 front-left
        0.5f, 0.0f,  0.5f,   1,1,1,    1,0,   0,-1,0,  // 1 front-right
        0.5f, 0.0f, -0.5f,   1,1,1,    1,1,   0,-1,0,  // 2 back-right
        -0.5f, 0.0f, -0.5f,   1,1,1,    0,1,   0,-1,0,  // 3 back-left

        // Sides (apex duplicated per face for correct normals)
        // Front face
        -0.5f, 0.0f,  0.5f,   1,1,1,    0,0,   0.0f,0.707f,0.707f,  // 4 front-left
        0.5f, 0.0f,  0.5f,   1,1,1,    1,0,   0.0f,0.707f,0.707f,  // 5 front-right
        0.0f, 0.8f,  0.0f,   1,1,1,    0.5,1,  0.0f,0.707f,0.707f, // 6 apex front

        // Right face
        0.5f, 0.0f,  0.5f,   1,1,1,    0,0,   0.707f,0.707f,0.0f,  // 7 front-right
        0.5f, 0.0f, -0.5f,   1,1,1,    1,0,   0.707f,0.707f,0.0f,  // 8 back-right
        0.0f, 0.8f,  0.0f,   1,1,1,    0.5,1,  0.707f,0.707f,0.0f, // 9 apex right

        // Back face
        0.5f, 0.0f, -0.5f,   1,1,1,    0,0,   0.0f,0.707f,-0.707f, // 10 back-right
        -0.5f, 0.0f, -0.5f,   1,1,1,    1,0,   0.0f,0.707f,-0.707f, // 11 back-left
        0.0f, 0.8f,  0.0f,   1,1,1,    0.5,1,  0.0f,0.707f,-0.707f,// 12 apex back

        // Left face
        -0.5f, 0.0f, -0.5f,   1,1,1,    0,0,   -0.707f,0.707f,0.0f,// 13 back-left
        -0.5f, 0.0f,  0.5f,   1,1,1,    1,0,   -0.707f,0.707f,0.0f,// 14 front-left
        0.0f, 0.8f,  0.0f,   1,1,1,    0.5,1,  -0.707f,0.707f,0.0f// 15 apex left
    };

    unsigned int indices[] = {
        // Base
        0, 1, 2,
        0, 2, 3,

        // Front
        4, 5, 6,

        // Right
        7, 8, 9,

        // Back
        10,11,12,

        // Left
        13,14,15
    };





    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    


    // stride = 11 floats
    GLsizei stride = 11 * sizeof(float);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // TexCoord
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // Normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);


    // ... after setting up vertex attrib pointers ...

    // Unbind VAO (allowed), but *do not* unbind the element array buffer while VAO is bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   // REMOVE this line!
    glBindVertexArray(0);

    // It's OK to unbind the VBO if you want:
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Importing texture
    stbi_set_flip_vertically_on_load(true);

    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load("./include/Textures/brick.png", &widthImg, &heightImg, &numColCh, 0);
    if (!bytes) {
        std::cerr << "Failed to load texture: ./include/Textures/brick.png\n";
        return -1;  // Handle error
    } else {
        std::cout << "Texture loaded: " << widthImg << "x" << heightImg << " with " << numColCh << " channels.\n";
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); // <-- BIND before setting params and uploading

    // texture settings (now apply to 'texture')
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Choose the format of the texture based on the number of color channels
    // If there are 4 color channels, use GL_RGBA, otherwise use GL_RGB
    GLenum format = (numColCh == 4 ? GL_RGBA : GL_RGB);
    
    // Upload the pixel data to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);
    
    // Generate mipmaps for the texture
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free the memory allocated for the image data
    stbi_image_free(bytes);

    // Unbind the texture
    glEnable(GL_DEPTH_TEST);

    // Main loop: handles rendering and event processing until the window is closed
    while (!glfwWindowShouldClose(Window::window))
    {
        // Process user input
        Window::processInput(Window::window);

        // Clear the screen and set the draw color
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Set the view and projection matrices in the shader
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);

        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        int modelLoc = glGetUniformLocation(shader.ID, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        int viewLoc = glGetUniformLocation(shader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        int projectionLoc = glGetUniformLocation(shader.ID, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));



        //Textures:
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // Bind the vertex array object and draw the triangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


        // Swap the front and back buffers and poll for events
        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    Window::terminateWindow();
    return 0;
}
