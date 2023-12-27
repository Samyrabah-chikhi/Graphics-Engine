#include "Light.h"

#define LIGHTTYPE int
#define DIRECTIONAL_LIGHT 0
#define POINT_LIGHT 1
#define SPOT_LIGHT 2
#define PHONG_LIGHT 3

std::vector<PointLight> PointLights;
std::vector<DirLight> DirLights;
std::vector <PhongLight> PhongLights;
bool lightExist = false;

void addLight(LIGHTTYPE type)
{
	lightExist = true;

	if (type == 0) {
		PointLight pt;
		pt.color = glm::vec3(1.0f, 1.0f, 1.0f);
		pt.position = glm::vec3(0.0f, 0.0f, 0.0f);
		
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
		dr.color = glm::vec3(1.0f, 1.0f, 1.0f);
		
		dr.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		dr.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		dr.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		DirLights.push_back(dr);
	}
	else if (type == 2) {

	}
	else if (type == 3) {
		PhongLight pl;
		pl.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		pl.lightPos = glm::vec3(1.0f, 0.0f, 1.0f);

		pl.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		pl.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
		pl.specular = glm::vec3(1.0f, 1.0f, 1.0f);

		PhongLights.push_back(pl);
	}
	else {
		printf("Error no like this exists\n");
	}
}
