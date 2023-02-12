#include"include/Camera.h"
#include "iostream"

using namespace std;

Camera::Camera(int width, int height)
{
    Camera::width = width;
    Camera::height = height;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    Orientation = glm::normalize(Target-Position);

    view = glm::lookAt(Position, Position + Orientation, Up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);

    cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
		
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Position -= glm::normalize(glm::cross(Orientation, glm::cross(Orientation, Up))) * speed;//speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Position += glm::normalize(glm::cross(Orientation, glm::cross(Orientation, Up))) * speed;//speed * Up;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Position += glm::normalize(glm::cross(Orientation, Up)) * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        Position += speed * Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        Position -= speed * Orientation;
    }   
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        Position = glm::vec3(0.0f, 0.0f, 10.0f);
        Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        // Up = glm::vec3(0.0f, 1.0f, 0.0f);
        // cameraMatrix = glm::mat4(1.0f);
    }   
}