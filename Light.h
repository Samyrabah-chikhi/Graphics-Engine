#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include <vector>

#define LIGHTTYPE int
#define POINT_LIGHT 0
#define DIRECTIONAL_LIGHT 1
#define SPOT_LIGHT 2

typedef struct DirLight {
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
}DirLight;

typedef struct PointLight {
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
}PointLight;

typedef struct SpotLight {
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;


}SpotLight;

extern std::vector <DirLight> DirLights;
extern std::vector <PointLight> PointLights;
extern std::vector <SpotLight> SpotLights;
extern bool lightExist ;

void addLight(LIGHTTYPE type);
void showDirLight(int index);
void showPointLight(int index);
void showSpotLight(int index);


    
    /*GLuint VAOLight, VBOLight;
    glGenVertexArrays(1, &VAOLight);
    glGenBuffers(1, &VBOLight);

    glBindVertexArray(VAOLight);  
    glBindBuffer(GL_ARRAY_BUFFER, VBOLight);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    OnDestroy(&VAOLight, &VBOLight, window);*/

#endif // LIGHT_H