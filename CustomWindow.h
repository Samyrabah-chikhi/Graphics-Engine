#pragma once
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void OnCreate(GLFWwindow** window, int width, int height);
void OnDestroy(GLuint* VAO, GLuint* VBO, GLFWwindow* window);
void CreatingWindow(GLFWwindow** window,int width,int height);

