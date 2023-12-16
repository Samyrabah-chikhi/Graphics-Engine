#include "inclusion.h"


void Light(unsigned char* data,unsigned char* indices,GLuint shader) {
	GLuint lightVAO;

	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	GLuint lightEBO,lightVBO;
	glGenBuffers(1, &lightVBO);
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0,(void*)0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	

	glUseProgram(shader);
}

