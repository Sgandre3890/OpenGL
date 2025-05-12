#include "Engine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #version 330 core

namespace Renderer {
	
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	void render () {
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}

namespace {
	void windowResizeCallback(GLFWwindow* window, int width, int height) { //for when the window gets resized
		glViewport(0, 0, width, height);
		Engine::SCR_WIDTH = Engine::SCR_WIDTH;
		Engine::SCR_HEIGHT = Engine::SCR_HEIGHT;
	}
}

namespace Engine {
    GLFWwindow* window;
	int SCR_WIDTH=800,SCR_HEIGHT=800,CAM_WIDTH=800,CAM_HEIGHT=600;
	int init(int SCR_WIDTH, int SCR_HEIGHT) {
		//Initialize
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Set Version
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //Use core version of OpenGL
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //FOR MACOS
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		//Create GLFW window
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL", NULL, NULL); //Size, title, monitor, shared recourses
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
		glViewport(0, 0, CAM_WIDTH, CAM_HEIGHT);
		Engine::SCR_WIDTH = SCR_WIDTH; Engine::SCR_HEIGHT = SCR_HEIGHT;
		Engine::CAM_WIDTH = CAM_WIDTH; Engine::CAM_HEIGHT = CAM_HEIGHT;
		glfwSetFramebufferSizeCallback(window,windowResizeCallback); //assigns resize callback function

		#ifdef __APPLE__
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		#endif
		
		return 0;
	}

	void loop() {
		while(!glfwWindowShouldClose(window)) {
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
			
			Renderer::render();
			glfwSwapBuffers(window); //swap front and back buffers
			glfwPollEvents();
		}
	}
}
