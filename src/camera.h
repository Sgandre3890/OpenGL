#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "shader.h"

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Orientation;
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

    int SCR_WIDTH;
    int SCR_HEIGHT;

    float speed = 0.1f;
    float sensitivity = 100.0f;

    Camera(int SCR_WIDTH, int SCR_HEIGHT, glm::vec3 position);

    void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
    void Inputs(GLFWwindow* window);
};

#endif