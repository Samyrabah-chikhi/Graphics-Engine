#include "Light.h"

#define LIGHTTYPE int
#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1
#define SPOT_LIGHT 2

std::vector<PointLight> PointLights;
std::vector<DirLight> DirLights;
std::vector <SpotLight> SpotLights; 
std::vector<Light*> Lights;

bool lightExist = false;

void addLight(LIGHTTYPE type)
{
	lightExist = true;

	if (type == 0) {

		PointLight pt;
		pt.position = glm::vec3(0.0f, 2.0f, 0.0f);
		
		pt.constant = 1.0f;
		pt.linear = 0.09f;
		pt.quadratic = 0.032f;
		

		pt.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		pt.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		pt.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		PointLights.push_back(pt);
	}
	else if (type == 1) {

		DirLight dr;
		dr.direction = glm::vec3(-1.0f,0.0f,-1.0f);
		
		dr.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		dr.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		dr.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		DirLights.push_back(dr);
	}
	else if (type == 2) {

		SpotLight sp;

		sp.position = glm::vec3(0.0f, 2.0f, 0.0f);;
		sp.direction = glm::vec3(0.0f, -1.0f, 0.0f);;

		sp.cutOff = glm::cos(glm::radians(12.5f));
		sp.outerCutOff = glm::cos(glm::radians(15.0f));

		sp.constant = 1.0f;
		sp.linear = 0.09f;
		sp.quadratic = 0.032f;

		sp.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
		sp.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		sp.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		SpotLights.push_back(sp);
	}
	else {
		printf("Error no like this exists\n");
	}
}



Light::Light(LIGHTRENDER type)
{
	if (!type) {
		glGenVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);
		glGenBuffers(1, &this->VBO);

		int length = sizeof(cubeMesh) / sizeof(float);

		for (int i = 0; i < length; i++) {
			this->vertex.push_back(cubeMesh[i]);
		}


		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeMesh), cubeMesh, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		Lights.push_back(this);
	}


}
void Light::render() {

	int length = sizeof(cubeMesh) / sizeof(float);

	for (int i = 0; i < SpotLights.size(); i++) {
		for (int j = 0; j < length; j+=3) {
			this->vertex[j] += SpotLights[i].position.x;
			this->vertex[j + 1] += SpotLights[i].position.y;
			this->vertex[j + 2] += SpotLights[i].position.z;

		}
		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, this->vertex.size());
	}

	

}