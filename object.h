#ifndef OBJECTS_H
#define OBJECTS_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class object
{
	static int numberOfObjects;

private:

	int indexOfObject;
	
	std::vector<float> vertex;
	std::vector<float> colors;
	std::vector<float> textures;
	std::vector<int> indices;

	glm::vec3 CustomColor;

	GLuint shaderID;
	GLuint TextureID;

	GLuint VAO,VBO,EBO;
	GLuint VBOColor, VBOTexture;

	bool indexExist;
	bool shaderExist;
	bool textureExist;
	bool materialExist;
	bool useCustomColor;

public:

	object(float* vertices, int numberOfVertices);
	object(float* vertices, int numberOfVertices, glm::vec3 origin);
	object(float* vertices, int numberOfVertices, int* indices, int numberOfIndices, glm::vec3 origin);
	object(float* vertices, int numberOfVertices, glm::vec3 origin,glm::vec3 customColor);

	void AddShader(float* colors, int numberOfColors);
	void Render(glm::mat4* mvp);
	void AddTexture();

	void translate(glm::vec3 translation);
	void rotate(glm::vec3 rotation,float angle);
	void scale(glm::vec3 scale);
private:
	void CreateShader();
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	void ProjectMesh(glm::mat4* mvp);

	
};

extern std::vector<object*> Objects;
#endif