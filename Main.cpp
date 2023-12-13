#include <iostream>
#include <Windows.h>

#include "inclusion.h"

#define width 800
#define height 800

typedef struct camera {
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    int widthCam, heightCam;
    float speed = 0.1f;
    float sensitivty = 100.0f;

    float lastX, lastY;

}camera;



void Draw();
void Transformation(GLuint shader, glm::vec3 translation, glm::vec3 rotation, glm::vec3 scaling, const char** Unif, float angle);
void CameraTransformation(GLuint shader, glm::vec3 axis, glm::vec3 eye, glm::vec3 center, glm::vec3 up, float FOV, float minClip, float maxClip, float angle,const char* uniform);
void Translate(GLuint shader, glm::vec3 translation, const char* Unif);
void Scale(GLuint shader, glm::vec3 scaling, const char* Unif);
void Rotate(GLuint shader, glm::vec3 rotation, float angle, const char* Unif);
void CameraMove(GLFWwindow* window, glm::vec3* Position, glm::vec3* Orientation, glm::vec3* Up, float* speed, float sensitivity, float* yaw, float* pitch, bool* firstMouse, float* lastX, float* lastY);

int main() {

    GLFWwindow* window;
    OnCreate(&window,width,height);

    int instanceNumber=10;

    float* instances;

    float vertices[] = {
        //Location          /Colors         //Texture map
        -0.5f,0.0f,0.5f,  0.7,0.6,0.5,     0.0f,0.0f,
        -0.5f,0.0f,-0.5f, 0.3f,0.3f,0.4f,  1.0f,0.0f,
        0.5f,0.0f,-0.5f,  0.2f,0.2f,0.8f,  0.0f,0.0f,
        0.5f,0.0f,0.5f,   0.5f,0.3f,0.1f,  1.0f,0.0f,
        0.0f,0.8f,0.0f,   0.6f,0.6f,0.1f,  0.5f,1.0f,
    };
    for (int i = 0; i < instanceNumber; i++) {

    }


    int indices[] = {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    GLuint shader = LoadShaders(
        "E:\\Assets\\Vertex shader.txt",
        "E:\\Assets\\Fragment shader.txt"
    );

    
    int widthImg, heightImg, colorChannel;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(
        "C:\\Users\\Administrator\\Pictures\\wall.jpg",
        &widthImg, &heightImg, &colorChannel, 0
    );

    GLuint texture;

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    //Parameters 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

    //Already in use
    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    //Time for bitmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    GLuint tex0Uni = glGetUniformLocation(shader, "tex0");
    glUniform1i(tex0Uni, 0);
 
    //Camera things

    glEnable(GL_DEPTH_TEST);

    float rotation = 0.0f;
    float prevTime = glfwGetTime(),crntTime;
    
    camera mainCamera;

    glm::vec3 position= glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 orientation= glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up= glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 rotationDir= glm::vec3(0.0f, 1.0f, 0.0f);


    float lastX=width/2, lastY=height/2;
    float yaw = -90.0f;
    float pitch = 0.0f;

    bool firstMouse = true;

    float initialFoV = 45.0f;
    float mouseSpeed = 0.005f;
    float speed = 0.05;

    //Main loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.3f, 0.3f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        glBindTexture(GL_TEXTURE_2D, texture);

        glEnableVertexAttribArray(VAO);

        crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60) {
            rotation += 3;
            prevTime = crntTime;
        }

        CameraTransformation(
            shader,
            rotationDir,
            position,
            orientation,
            up,
            initialFoV,
            0.1,
            100,
            0,
            "mvp"
        );

        //CameraMove(window, Position, Orientation, Up,speed,*sensitivity,yaw,pitch, firstMouse, lastX, lastY)
        CameraMove(window, &position, &orientation, &up, &speed, mouseSpeed,&yaw,&pitch,&firstMouse,&lastX,&lastY);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int) , GL_UNSIGNED_INT, 0);



        glfwSwapBuffers(window);
        glfwPollEvents();
       
        
    }
    glDeleteShader(shader);
    glDeleteBuffers(1, &EBO);
    OnDestroy(&VAO, &VBO, window);

    return 0;
}

void Draw() {


}
void Translate(GLuint shader, glm::vec3 translation, const char* Unif) {

    glm::mat4 myTranslation = glm::translate(glm::mat4(1), translation);
    glUniformMatrix4fv(glGetUniformLocation(shader, Unif), 1, GL_FALSE, glm::value_ptr(myTranslation));

}
void Rotate(GLuint shader, glm::vec3 rotation, float angle, const char* Unif) {
    glm::mat4 myRotation = glm::rotate(angle, rotation);
    glUniformMatrix4fv(glGetUniformLocation(shader, Unif), 1, GL_FALSE, glm::value_ptr(myRotation));
}
void Scale(GLuint shader, glm::vec3 scaling, const char* Unif) {
    glm::mat4 myScaling = glm::scale(scaling);
    glUniformMatrix4fv(glGetUniformLocation(shader, Unif), 1, GL_FALSE, glm::value_ptr(myScaling));
}

void Transformation(GLuint shader,glm::vec3 translation, glm::vec3 rotation, glm::vec3 scaling,const char** Unif,float angle) {
   
    
}



void CameraTransformation(GLuint shader,glm::vec3 axis,glm::vec3 position,glm::vec3 orientation,glm::vec3 up,float FOV,float minClip,float maxClip,float angle,const char* uniform) {

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(angle), axis);
    glm::mat4 view = glm::lookAt(
        position,
        position+orientation,
        up
    );
    glm::mat4 projection = glm::perspective(glm::radians(FOV), (float)width / height, minClip, maxClip);

    glm::mat4 mvp = projection * view * model;

    GLuint matrixID = glGetUniformLocation(shader, uniform);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
}

void CameraMove(GLFWwindow* window,glm::vec3* Position,glm::vec3* Orientation,glm::vec3* Up,float* speed,float sensitivity, float* yaw, float* pitch,bool* firstMouse,float* lastX,float* lastY) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        *Position += *speed * *Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        *Position += *speed * -*Orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        *Position += *speed * -glm::normalize(glm::cross(*Orientation,*Up));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        *Position += *speed * glm::normalize(glm::cross(*Orientation, *Up));
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        *Position += *speed * *Up;
    }
    if(glfwGetKey(window,GLFW_KEY_E)==GLFW_PRESS){
        *Position += *speed * -*Up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ) {
        *speed = 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
        *speed = 0.05;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        *Position = glm::vec3(0.0f, 0.0f, 5.0f);
        *Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        *lastX = width / 2;
        *lastY = height / 2;
        *yaw = -90.0f;
        *pitch = 0.0f;
    }
    //Moving on X,Y,Z
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        double xpos, ypos;
        glfwGetCursorPos(window,&xpos, &ypos);

        //std::cout << "LastX : " << *lastX << " LastY : " << *lastY << std::endl;;
        //std::cout << "X : " << xpos << " Y : " << ypos << std::endl;;
        if (*firstMouse)
        {
            *lastX = xpos;
            *lastY = ypos;
            *firstMouse = false;
        }

        float xoffset = xpos - *lastX;
        float yoffset = *lastY - ypos;
        *lastX = xpos;
        *lastY = ypos;

        float sensitivity = 0.1f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        *yaw += xoffset;
        *pitch += yoffset;

        if (*pitch > 88.0f)
            *pitch = 88.0f;
        if (*pitch < -88.0f)
            *pitch = -88.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(*yaw)) * cos(glm::radians(*pitch));
        direction.y = sin(glm::radians(*pitch));
        direction.z = sin(glm::radians(*yaw)) * cos(glm::radians(*pitch));
        *Orientation = glm::normalize(direction);

       
    }
    else if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT)==GLFW_RELEASE){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
         *firstMouse = true;
    }
   
}
