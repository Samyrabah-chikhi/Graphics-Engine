#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include <vector>

#include "Utilities.h"

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


#define LIGHTRENDER int
#define CUBE 0
#define SPHERE 1


class Light {

    GLuint VAO, VBO, EBO;
    
    std::vector<float> vertex;

public:
    Light(LIGHTRENDER type);
    void render();

};

extern std::vector<Light*> Lights;

#endif 