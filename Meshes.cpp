#include "Meshes.h"

float vertex[] = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
};

void generateCube(glm::vec3 position, glm::vec3 scale, GLuint* VBO,float** data) {
	
	float copy[36];
	for (int i = 0; i < 36; i++) {
		copy[i] = vertex[i];
	}

	for (int i = 0; i < 36; i += 3) {
		copy[i] *= scale.x;
		copy[i + 1] *= scale.y;
		copy[i + 2] *= scale.z;
	}

	for (int i = 0; i < 36; i+=3) {
		copy[i] += position.x;
		copy[i+1] += position.y;
		copy[i+2] += position.z;
	}
	glGenBuffers(1, VBO);
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(copy), copy, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	glEnableVertexAttribArray(0);


	*data = copy;
}

void showMesh(GLuint VBO) {
       
    GLuint shader = LoadShaders(
            "E:\\Assets\\Vertex Shader Mesh.txt",
            "E:\\Assets\\Fragment shader Mesh.txt"
        );

	glUseProgram(shader);

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glDrawArrays(GL_TRIANGLES, 0, 36);

}

void destroyMesh(GLuint* VBO) {
	glDeleteBuffers(1, VBO);
}