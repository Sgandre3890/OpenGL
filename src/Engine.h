#ifndef Engine_h
#define Engine_h

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

namespace Engine {
	extern GLFWwindow* window;
	extern int width, height;
	
	int init(int ScreenW, int ScreenH); 
	void loop();
}

#endif Engine_h