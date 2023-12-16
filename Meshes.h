#include "inclusion.h"

extern float vertex[];

void generateCube(glm::vec3 position, glm::vec3 scale, GLuint* VBO, float** copy);
void showMesh(GLuint VBO);
void destroyMesh(GLuint* VBO);