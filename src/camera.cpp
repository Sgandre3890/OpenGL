#include "camera.h"


Camera::Camera(int SCR_WIDTH, int SCR_HEIGHT, glm::vec3 position)
{
    this->SCR_WIDTH = SCR_WIDTH;
    this->SCR_HEIGHT = SCR_HEIGHT;
    Position = position;
    Orientation = glm::vec3(0.0f, 0.0f, -1.0f); 
}


void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg),(float)SCR_WIDTH / (float)SCR_HEIGHT,nearPlane, farPlane);

    camMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) 
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
    // --- Movement ---
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Position += speed * Orientation;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Position -= speed * Orientation;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Orientation, Up)) * speed;

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Position += Up * speed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        Position -= Up * speed;

    // --- Mouse look ---
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        if (firstClick)
        {
            // Reset mouse to center on first click, no sudden snap
            glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);
            firstClick = false;
            return; // skip this frame
        }

        // Calculate rotation amounts relative to screen center
        float rotX = sensitivity * (float)(mouseY - (SCR_HEIGHT / 2)) / (SCR_HEIGHT / 2);
        float rotY = sensitivity * (float)(mouseX - (SCR_WIDTH / 2)) / (SCR_WIDTH / 2);

        // Pitch: rotate around right axis
        glm::vec3 right = glm::normalize(glm::cross(Orientation, Up));
        glm::mat4 pitchMat = glm::rotate(glm::mat4(1.0f), glm::radians(-rotX), right);
        glm::vec3 newOrientation = glm::mat3(pitchMat) * Orientation;

        // Clamp pitch
        float pitchAngle = glm::degrees(glm::asin(newOrientation.y));
        if (pitchAngle < 85.0f && pitchAngle > -85.0f)
            Orientation = newOrientation;

        // Yaw: rotate around global Up
        glm::mat4 yawMat = glm::rotate(glm::mat4(1.0f), glm::radians(-rotY), Up);
        Orientation = glm::mat3(yawMat) * Orientation;

        // Normalize to avoid drift
        Orientation = glm::normalize(Orientation);

        // Recenter cursor
        glfwSetCursorPos(window, SCR_WIDTH / 2, SCR_HEIGHT / 2);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true; // reset for next time
    }
}



