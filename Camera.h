#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Windows.h>

#include <vector>
#include "object.h"
#include "Light.h"

class Camera
{

private:
    GLFWwindow* window;

    glm::vec3 position;
    glm::vec3 orientation;
    glm::vec3 up;


    float width, height;

    float lastX,lastY;
    float yaw;
    float pitch;

    bool firstMouse;

    float FOV;
    float sensitivity;
    float speed;
    
    float minClip, maxClip;

    glm::mat4* mvp;

    bool LockCamera;

public:
    Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 orientation);
    Camera(GLFWwindow* window, glm::vec3 position, glm::vec3 orientation, glm::vec3 up,float width,float height,float FOV);
    void TransformCamera();
    void CameraMove(GLFWwindow* window);
    void render(std::vector<object*> Object);
    void UpdateLight();
    glm::mat4* getMvp();
    void enableDepth();
    void RenderLight(object* Object, int indices);
};

