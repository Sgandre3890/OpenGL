#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Engine.h"

using namespace std;


int main()
{
    Engine::init(800,600);
    Engine::loop();

    return 0;
}

