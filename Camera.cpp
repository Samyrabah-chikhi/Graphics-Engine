#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 Position)
{
	Camera::width = width;
	Camera::height = height;
	Position = Position;
}

void Camera::Matrix(float FOV, float nearPlane, float farPlane, GLuint shader, const char* Uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(
		Position, 
		Position + Orientation, 
		Up
	);
	projection = glm::perspective(
		FOV, 
		float(width / height), 
		nearPlane, 
		farPlane
	);

	glUniformMatrix4fv(
		glGetUniformLocation(shader,Uniform), 
		1, GL_FALSE, 
		glm::value_ptr(projection*view)
	);
}


void Camera::Inputs(GLFWwindow* window)
{



}
