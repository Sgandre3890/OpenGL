#include "Engine.h"

namespace {
	void windowResizeCallback(GLFWwindow* window, int width, int height) { //for when the window gets resized
		glViewport(0, 0, width, height);
		Engine::width = width;
		Engine::height = height;
	}
}

namespace Engine {
    GLFWwindow* window;
	int width,height;
	int init(int ScreenW, int ScreenH) {
		//Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Set Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core version of OpenGL
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //FOR MACOS
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		//Create GLFW window
		window = glfwCreateWindow(ScreenW, ScreenH, "OpenGL", NULL, NULL); //Size, title, monitor, shared recourses
		if (window == NULL) {
			cout << "Failed to create GLFW window" << endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);


		//Initialize GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			cout << "Failed to initialize GLAD" << endl;
			return -1;
		}

		//Sets GL Viewport (camera)
		glViewport(0, 0, width, height);
		Engine::width = width;
		Engine::height = height;
		glfwSetFramebufferSizeCallback(window,windowResizeCallback); //assigns resize callback function

		// #ifdef __APPLE__
		// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// #endif

		return 0;
	}

	void loop() {
		while(!glfwWindowShouldClose(window)) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

}