#ifndef Engine_h
#define Engine_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

namespace Renderer {
	void render();
	extern float vertices[];

}

namespace Engine {
	extern GLFWwindow* window;
	extern int width, height;
	extern int Cwidth, Cheight;
	
	int init(int width, int height); 
	void loop();
}

#endif