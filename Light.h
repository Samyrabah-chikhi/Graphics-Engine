//#include <glm/glm.hpp>
//#include <glm/gtx/transform.hpp> 
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include "glad/glad.h"
//#include <vector>
//
//#define LIGHTTYPE int
//#define DIRECTIONAL_LIGHT 0
//#define POINT_LIGHT 1
//#define SPOT_LIGHT 2
//#define PHONG_LIGHT 3
//
//
//typedef struct DirLight {
//    glm::vec3 direction;
//    glm::vec3 color;
//
//    glm::vec3 ambient;
//    glm::vec3 diffuse;
//    glm::vec3 specular;
//}DirLight;
//
//typedef struct PhongLight {
//    glm::vec3 lightPos;
//    glm::vec3 lightColor;
//    float ambientStrength;
//    float specular;
//}PhongLight;
//
//typedef struct PointLight {
//    glm::vec3 position;
//    glm::vec3 color;
//
//    float constant;
//    float linear;
//    float quadratic;
//
//    glm::vec3 ambient;
//    glm::vec3 diffuse;
//    glm::vec3 specular;
//}PointLight;
//
//
//extern std::vector <PointLight> PointLights;
//extern std::vector <DirLight> DirLights;
//
//extern bool lightExist;
//
//void add(LIGHTTYPE type);
//
//
//
//
//
//
//    
//    /*GLuint VAOLight, VBOLight;
//    glGenVertexArrays(1, &VAOLight);
//    glGenBuffers(1, &VBOLight);
//
//    glBindVertexArray(VAOLight);  
//    glBindBuffer(GL_ARRAY_BUFFER, VBOLight);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//
//    OnDestroy(&VAOLight, &VBOLight, window);*/
//
//    