#ifndef Engine_h
#define Engine_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

namespace Renderer {
	void color();
	extern float vertices[];

}

namespace Engine {
	extern GLFWwindow* window;
	extern int SCR_WIDTH, SCR_HEIGHT;
	extern int CAM_WIDTH, CAM_HEIGHT;
	
	int init(int SCR_WIDTH, int SCR_HEIGHT); 
	void loop();
}

#endif