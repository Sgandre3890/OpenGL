#include "camera.h"

Camera::Camera(int SCR_WIDTH, int SCR_HEIGHT, glm::vec3 position)
{
    this->SCR_WIDTH = SCR_WIDTH;
    this->SCR_HEIGHT = SCR_HEIGHT;
    Position = position;
    Orientation = glm::vec3(0.0f, 0.0f, -1.0f); 
}


void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg),(float)SCR_WIDTH / (float)SCR_HEIGHT,nearPlane, farPlane);
    Orientation = glm::vec3(0.0f, 0.0f, -1.0f); 

    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}