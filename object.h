#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

class object
{
	static int numberOfObjects;

private:

	int indexOfObject;
	
	std::vector<float> vertex;
	std::vector<float> colors;
	std::vector<float> textures;

	std::vector<int> indices;

	GLuint shaderID;
	GLuint TextureID;

	GLuint VAO,VBO,EBO;
	GLuint VBOColor, VBOTexture;

	bool indexExist;
	bool shaderExist;
	bool textureExit;

public:

	static std::vector<object> Object;

	object(float* vertices, int numberOfVertices);
	object(float* vertices, int numberOfVertices, int* indices, int numberOfIndices);
	void AddShader(float* colors, int numberOfColors);
	void Render(glm::mat4* mvp);
	void AddTexture();


private:
	void CreateShader();
	GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
	void ProjectMesh(glm::mat4* mvp);

	
};

