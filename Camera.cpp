#include "Camera.h"


Camera::Camera(GLFWwindow* window, glm::vec3 position,glm::vec3 orientation)
{
    this->LockCamera = false;

    this->position = position;
    this->orientation = orientation;
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->FOV = 45.0f;

    this->width = 1080;
    this->height = 1080;

    this->yaw = -90.f;
    this->pitch = 0.0f;

    this->lastX = this->width / 2;
    this->lastY = this->height / 2;

    this->sensitivity = 0.1f;
    this->speed = 0.05;

    this->firstMouse = true;

    this->minClip = 0.01f;
    this->maxClip = 100.0f;

    this->window = window;
   
    TransformCamera();
    enableDepth();
}

Camera::Camera(GLFWwindow* window,glm::vec3 position, glm::vec3 orientation, glm::vec3 up, float width, float height, float FOV)
{
    this->position = position;
    this->orientation = orientation;
    this->up = up;

    this->FOV = FOV;

    this->width = width;
    this->height = height;
       
    this->yaw = -90.f;
    this->pitch = 0.0f;

    this->lastX = this->width / 2; 
    this->lastY = this->height / 2;

    this->sensitivity = 0.1f;
    this->speed = 0.05;

    this->firstMouse = true;

    this->minClip = 0.01f;
    this->maxClip = 100.0f;
    
    this->window = window;


    TransformCamera();
    enableDepth();
}


void Camera::CameraMove(GLFWwindow* window) {

        double xpos, ypos;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            this->position += this->speed * this->orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            this->position += this->speed * -this->orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            this->position += this->speed * -glm::normalize(glm::cross(this->orientation, this->up));
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            this->position += this->speed * glm::normalize(glm::cross(this->orientation, this->up));
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
            this->position += this->speed * this->up;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
            this->position += this->speed * -this->up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            this->speed = 0.01;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
            this->speed = 0.05;
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            this->position = glm::vec3(0.0f, 0.0f, 5.0f);
            this->orientation = glm::vec3(0.0f, 0.0f, -1.0f);
            this->up = glm::vec3(0.0f, 1.0f, 0.0f);
            this->lastX = this->width / 2;
            this->lastY = this->height / 2;
            this->yaw = -90.0f;
            this->pitch = 0.0f;
        }
        //Moving on X,Y,Z
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


            glfwGetCursorPos(window, &xpos, &ypos);

            if (this->firstMouse)
            {
                this->lastX = xpos;
                this->lastY = ypos;
                this->firstMouse = false;
            }

            float xoffset = xpos - this->lastX;
            float yoffset = this->lastY - ypos;
            this->lastX = xpos;
            this->lastY = ypos;

            xoffset *= this->sensitivity;
            yoffset *= this->sensitivity;

            this->yaw += xoffset;
            this->pitch += yoffset;

            if (this->pitch > 88.0f)
                this->pitch = 88.0f;
            if (this->pitch < -88.0f)
                this->pitch = -88.0f;

            glm::vec3 direction;
            direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
            direction.y = sin(glm::radians(this->pitch));
            direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
            this->orientation = glm::normalize(direction);

        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            this->firstMouse = true;
        }

}






void Camera::TransformCamera() {

    this->mvp = new glm::mat4[3];

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 view = glm::lookAt(
        this->position,
        this->position + this->orientation,
        this->up
    );
    glm::mat4 projection = glm::perspective(glm::radians(this->FOV), this->width / this->height, this->minClip, this->maxClip);
    this->mvp[0] = model;
    this->mvp[1] = view;
    this->mvp[2] = projection;

}

glm::mat4* Camera::getMvp() {
    return this->mvp;
}

void Camera::enableDepth()
{
    glEnable(GL_DEPTH_TEST);
}

void Camera::render(std::vector<object*> Object)
{
    int length = Objects.size();


    for (int i = 0; i < length; i++) {
        Object[i]->SetViewPos(this->position);
        Object[i]->Render(this->mvp);

        glUniform1i(glGetUniformLocation(Object[i]->GetShaderID(), "lightExist"),
            lightExist);

        glUniform1i(glGetUniformLocation(Object[i]->GetShaderID(), "nbrDirLight"),
            int(DirLights.size()));

        glUniform1i(glGetUniformLocation(Object[i]->GetShaderID(), "nbrPointLight"),
            int(PointLights.size()));
       
        glUniform1i(glGetUniformLocation(Object[i]->GetShaderID(), "nbrSpotLight"),
            int(SpotLights.size()));
        

        for (int j = 0; j < DirLights.size(); j++) 
            this->RenderDirLight(Object[i], j);
        
        for (int j = 0; j < PointLights.size(); j++) 
            this->RenderPointLight(Object[i], j);
        
        for (int j = 0; j < SpotLights.size(); j++) {
            //std::cout << SpotLights[j].cutOff << std::endl;
            this->RenderSpotLight(Object[i], j);
        }
            
        
    }

}


void Camera::RenderDirLight(object* Object, int indices)
{
    GLuint shader = Object->GetShaderID();
    std::string uniform;


    uniform = "dirLights[" + std::to_string(indices) + "].direction";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f, 
        glm::value_ptr(DirLights[indices].direction));

    uniform = "dirLights[" + std::to_string(indices) + "].ambient";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(DirLights[indices].ambient));

    uniform = "dirLights[" + std::to_string(indices) + "].diffuse";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f, 
        glm::value_ptr(DirLights[indices].diffuse));

    uniform = "dirLights[" + std::to_string(indices) + "].specular";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f, 
        glm::value_ptr(DirLights[indices].specular));
}

void Camera::RenderPointLight(object* Object, int indices)
{
    GLuint shader = Object->GetShaderID();
    std::string uniform;

    uniform = "pointLights[" + std::to_string(indices) + "].position";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(PointLights[indices].position));

    uniform = "pointLights[" + std::to_string(indices) + "].constant";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), PointLights[indices].constant);

    uniform = "pointLights[" + std::to_string(indices) + "].linear";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), PointLights[indices].linear);

    uniform = "pointLights[" + std::to_string(indices) + "].quadratic";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), PointLights[indices].quadratic);

    uniform = "pointLights[" + std::to_string(indices) + "].ambient";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(PointLights[indices].ambient));

    uniform = "pointLights[" + std::to_string(indices) + "].diffuse";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(PointLights[indices].diffuse));

    uniform = "pointLights[" + std::to_string(indices) + "].specular";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(PointLights[indices].specular));
}

void Camera::RenderSpotLight(object* Object, int indices)
{
    GLuint shader = Object->GetShaderID();
    std::string uniform;
    
    uniform = "spotLights[" + std::to_string(indices) + "].position";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(SpotLights[indices].position));

    uniform = "spotLights[" + std::to_string(indices) + "].direction";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(SpotLights[indices].direction));

    uniform = "spotLights[" + std::to_string(indices) + "].cutOff";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), SpotLights[indices].cutOff);

    uniform = "spotLights[" + std::to_string(indices) + "].outerCutOff";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), SpotLights[indices].outerCutOff);

    uniform = "spotLights[" + std::to_string(indices) + "].ambient";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(SpotLights[indices].ambient));

    uniform = "spotLights[" + std::to_string(indices) + "].diffuse";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(SpotLights[indices].diffuse));

    uniform = "spotLights[" + std::to_string(indices) + "].specular";
    glUniform3fv(glGetUniformLocation(shader, uniform.c_str()), 1.0f,
        glm::value_ptr(SpotLights[indices].specular));

    uniform = "spotLights[" + std::to_string(indices) + "].constant";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), SpotLights[indices].constant);

    uniform = "spotLights[" + std::to_string(indices) + "].linear";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), SpotLights[indices].linear);

    uniform = "spotLights[" + std::to_string(indices) + "].quadratic";
    glUniform1f(glGetUniformLocation(shader, uniform.c_str()), SpotLights[indices].quadratic);
}
