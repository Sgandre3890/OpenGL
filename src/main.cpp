#include "Model.h"
#include "Window.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main()
{
    if (Window::initializeWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL") != 0)
        return -1;

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("include/shaders/default.vert", "include/shaders/default.frag");

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    
    glEnable(GL_DEPTH_TEST);

    //Camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	Model model("include/Models/map/scene.gltf");

	glfwSwapInterval(1); // Enable V-Sync (limit FPS to monitor refresh rate)
	//glfwSwapInterval(0); // Disable V-Sync (no FPS limit, runs as fast as possible)

    // Main loop: handles rendering and event processing until the window is closed
    while (!glfwWindowShouldClose(Window::window))
    {
        // Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Window::processInput(Window::window);

		camera.Inputs(Window::window);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		model.Draw(shaderProgram, camera);

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(Window::window);
		// Take care of all GLFW events
		glfwPollEvents();
    }


	// Delete all the objects we've created
	shaderProgram.Delete();

    Window::terminateWindow();
    return 0;
}
