#include "master.h"

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
    GLfloat vertices[] =
    { //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
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

    // Indices for vertices order
    GLuint indices[] =
    {
        0, 1, 2, // Bottom side
        0, 2, 3, // Bottom side
        4, 6, 5, // Left side
        7, 9, 8, // Non-facing side
        10, 12, 11, // Right side
        13, 15, 14 // Facing side
    };
    /*
    GLfloat lightVertices[] = 
    {
        -0.1f, -0.1f,  0.1f,
        0.1f, -0.1f,  0.1f,
        0.1f,  0.1f,  0.1f,
        -0.1f,  0.1f,  0.1f
    };

    GLuint lightIndices[] = {
        0, 1, 2,
        0, 2, 3
    };
    */




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

    // Unbind VAO (allowed), but *do not* unbind the element array buffer while VAO is bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);   
    glBindVertexArray(0);

    // It's OK to unbind the VBO if you want:
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Importing texture
    stbi_set_flip_vertically_on_load(true);

    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load("./include/Textures/marble.jpg", &widthImg, &heightImg, &numColCh, 0);
    if (!bytes) {
        std::cerr << "Failed to load texture: ./include/Textures/marble.jpg\n";
        return -1;  
    } else {
        std::cout << "Texture loaded: " << widthImg << "x" << heightImg << " with " << numColCh << " channels.\n";
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture); 

    // texture settings 
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

    //Camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    // Main loop: handles rendering and event processing until the window is closed
    while (!glfwWindowShouldClose(Window::window))
    {
        // Process user input
        Window::processInput(Window::window);

        // Clear the screen and set the draw color
        glClearColor(0.2f, 0.3f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        

        //Inputs
        camera.Inputs(Window::window);
        //Camera matrix
        camera.Matrix(shader, "ViewMatrix");
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
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
