//#include "Light.h"
//
//std::vector<PointLight> PointLights;
//std::vector<DirLight> DirLights;
//bool lightExist = false;
//
//void add(LIGHTTYPE type)
//{
//	lightExist = true;
//
//	if (type == 0) {
//		PointLight pt;
//		pt.color = glm::vec3(1.0f, 1.0f, 1.0f);
//		pt.position = glm::vec3(0.0f, 0.0f, 0.0f);
//		
//		pt.constant = 1.0f;
//		pt.quadratic = 0.5f;
//		pt.linear = 0.5f;
//
//		pt.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
//		pt.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
//		pt.specular = glm::vec3(1.0f, 1.0f, 1.0f);
//
//		PointLights.push_back(pt);
//	}
//	if (type == 1) {
//
//		DirLight dr;
//		dr.direction = glm::vec3(-1.0f,1.0f,-1.0f);
//		dr.color = glm::vec3(1.0f, 1.0f, 1.0f);
//		
//		dr.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
//		dr.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
//		dr.specular = glm::vec3(1.0f, 1.0f, 1.0f);
//
//		DirLights.push_back(dr);
//	}
//	else {
//		printf("Error no like this exists\n");
//	}
//}
