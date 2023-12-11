#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CustomWindow.h"

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width, height;
	float speed = 0.1f;
	float sensitivty = 100.0f;

	Camera(int width, int height, glm::vec3 Position);
	void Matrix(float FOV, float nearPlane, float farPlane, GLuint shader, const char* Uniform);
	void Inputs(GLFWwindow* window);

};
#endif
