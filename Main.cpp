#include <iostream>
#include <Windows.h>

#include "object.h"
#include "inclusion.h"

#define PI 3.14159
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

void CameraMove(GLFWwindow* window, glm::vec3* Position, glm::vec3* Orientation, glm::vec3* Up, float* speed, float sensitivity, float* yaw, float* pitch, bool* firstMouse, float* lastX, float* lastY);
void CameraTransformation(GLuint shader, glm::vec3 position, glm::vec3 orientation, glm::vec3 up, float FOV, float minClip, float maxClip);

void Translate(GLuint shader, glm::vec3 translation);
void Scale(GLuint shader, glm::vec3 scaling);
void Rotate(GLuint shader, glm::vec3 rotationDir, float angle);

void InitCamera(glm::mat4** mvp, glm::vec3 position, glm::vec3 orientation, glm::vec3 up, float FOV, float minClip, float maxClip);
void ProjectMesh(GLuint shader, glm::mat4* mvp);

int main() {

    
    GLFWwindow* window;
    OnCreate(&window,width,height);

    float cubeMesh[] = {
   -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
   -0.5f,  0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,

   -0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,
   -0.5f, -0.5f,  0.5f,

   -0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f, -0.5f,
   -0.5f, -0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,

    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,

   -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, -0.5f,  0.5f,
    0.5f, -0.5f,  0.5f,
   -0.5f, -0.5f,  0.5f,
   -0.5f, -0.5f, -0.5f,

   -0.5f,  0.5f, -0.5f,
    0.5f,  0.5f, -0.5f,
    0.5f,  0.5f,  0.5f,
    0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f,  0.5f,
   -0.5f,  0.5f, -0.5f,
    };

    float vertex[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};//Cube

    printf("[%d]", sizeof(cubeMesh) / sizeof(float));
     object pp = object(cubeMesh,sizeof(cubeMesh)/sizeof(float));

    glm::vec3 customColor(0.47, 0.52, 0.12);

    float vertices[] = {
        //Location          /Colors         //Texture map
        -0.5f,0.0f,0.5f,  customColor.x,customColor.y,customColor.z,     0.0f,0.0f,
        -0.5f,0.0f,-0.5f, customColor.x,customColor.y,customColor.z,   1.0f,0.0f,
        0.5f,0.0f,-0.5f,  customColor.x,customColor.y,customColor.z,   0.0f,0.0f,
        0.5f,0.0f,0.5f,   customColor.x,customColor.y,customColor.z,   1.0f,0.0f,
        0.0f,0.8f,0.0f,   customColor.x,customColor.y,customColor.z,   0.5f,1.0f,
    };

    int indices[] = {
        0,1,2,
        0,2,3,
        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };

    GLuint VAO,VAOLight,VBOLight, VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    GLuint shader = LoadShaders(
        "E:\\Assets\\Vertex shader.txt",
        "E:\\Assets\\Fragment shader.txt"
    );
    
    //Light

    glGenVertexArrays(1, &VAOLight);
    glGenBuffers(1, &VBOLight);

    glBindVertexArray(VAOLight);  
    glBindBuffer(GL_ARRAY_BUFFER, VBOLight);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint lightShader = LoadShaders(
        "E:\\Assets\\Vs.txt",
        "E:\\Assets\\Fs.txt"
    );
   

    //Camera things

    glEnable(GL_DEPTH_TEST);

    float rotation = 0.0f;
    float prevTime = glfwGetTime(),crntTime;
    
    //Make a struct containing all 

    camera mainCamera;


    glm::vec3 position= glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 orientation= glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up= glm::vec3(0.0f, 1.0f, 0.0f);


    float lastX=width/2, lastY=height/2;
    float yaw = -90.0f;
    float pitch = 0.0f;

    bool firstMouse = true;

    float initialFoV = 45.0f;
    float mouseSpeed = 0.1f;
    float speed = 0.05;

    glm::vec3 lightPos(0.6f, 1.0f, 1.0f);

    float r = 2.0f;
    float red=1.0f, blue=0.0f, green=-0.3;

    glm::mat4* mvp;
    //Main loop
    while (!glfwWindowShouldClose(window)) {

        InitCamera(&mvp, position, orientation, up, initialFoV, 0.1, 100);

        glClearColor(0.05f, 0.05f, 0.05f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        pp.Render(mvp);


        glBindVertexArray(VAO);
        glUseProgram(shader);
  

        glUniform3f(glGetUniformLocation(shader, "lightColor"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(shader, "customColor"), 0.18f, 0.22f, 0.3f);
        glUniform3f(
            glGetUniformLocation(shader, "lightPos"), 
            r* cos(rotation), 
            r*sin(rotation),
            r* sin(rotation)
        );
        glUniform3f(glGetUniformLocation(shader, "viewPos"), position.x,position.y,position.z);

        crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60) {

            blue += 0.01;

            rotation += 0.005;
            prevTime = crntTime;

            CameraMove(
                window,
                &position,
                &orientation,
                &up,
                &speed,
                mouseSpeed,
                &yaw,
                &pitch,
                &firstMouse,
                &lastX,
                &lastY
            );
        }    

        CameraTransformation(
            shader,
            position,
            orientation,
            up,
            initialFoV,
            0.1,
            100
        );           
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glBindVertexArray(VAOLight);
        glUseProgram(lightShader);

        glUniform3f(glGetUniformLocation(lightShader, "lightColor"),1.0f, 1.0f, 1.0f);
        
        CameraTransformation(
            lightShader,
            position,
            orientation,
            up,
            initialFoV,
            0.1,
            100
        );

        glm::mat4 model = glm::mat4(1.0f);
        /*model = glm::translate(
            model, 
            lightPos 
        );*/
        model = glm::translate(model, glm::vec3(r * cos(rotation), r * sin(rotation), r * sin(rotation)));
        model = glm::rotate(model, rotation, glm::vec3(0.0, 1.0, 0.0));
        model = glm::scale(model, glm::vec3(0.2f));

        glUniformMatrix4fv(glGetUniformLocation(lightShader, "model"), 1, GL_FALSE, &model[0][0]);


        glDrawArrays(GL_TRIANGLES, 0, 36);

        

        glfwSwapBuffers(window);
        glfwPollEvents();
       
        
    }


    glDeleteShader(shader);
    OnDestroy(&VAO, &VBO, window);

    return 0;
}

void Translate(GLuint shader, glm::vec3 translation) {

     glm::mat4 model = glm::mat4(1.0f);
     model = glm::translate(model, translation);
     glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);

}

void Scale(GLuint shader, glm::vec3 scaling) {
    glm::mat4 model;
    model = glm::scale(model, scaling);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);
}
void Rotate(GLuint shader, glm::vec3 rotationDir, float angle) {
    glm::mat4 model;
    model = glm::rotate(angle, rotationDir);
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);
}

void ProjectMesh(GLuint shader,glm::mat4* mvp) {

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &mvp[0][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &mvp[1][0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &mvp[2][0][0]);
}
void InitCamera(glm::mat4** mvp, glm::vec3 position, glm::vec3 orientation, glm::vec3 up, float FOV, float minClip, float maxClip) {

    *mvp = (glm::mat4*)malloc(sizeof(glm::mat4) * 3);

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 view = glm::lookAt(
        position,
        position + orientation,
        up
    );
    glm::mat4 projection = glm::perspective(glm::radians(FOV), (float)width / height, minClip, maxClip);
    (*mvp)[0] = model;
    (*mvp)[1] = view;
    (*mvp)[2] = projection;
}

void CameraTransformation(GLuint shader, glm::vec3 position, glm::vec3 orientation, glm::vec3 up, float FOV, float minClip, float maxClip) {

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 view = glm::lookAt(
        position,
        position + orientation,
        up
    );
    glm::mat4 projection = glm::perspective(glm::radians(FOV), (float)width / height, minClip, maxClip);

    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, &model[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, &projection[0][0]);
}

void CameraMove(GLFWwindow* window,glm::vec3* Position,glm::vec3* Orientation,glm::vec3* Up,float* speed,float sensitivity, float* yaw, float* pitch,bool* firstMouse,float* lastX,float* lastY) {
    
    double xpos, ypos;
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);

    }
    
    
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

/*void drawSphere(float** vertices, GLfloat r, GLint lats, GLint longs)
{
    *vertices = (float*)malloc(sizeof(lats*longs));

    int i, j;
    for (i = 0; i <= lats; i++)
    {
        double lat0 = PI * (-0.5 + (double)(i - 1) / lats);
        double z0 = sin(lat0) * r;
        double zr0 = cos(lat0) * r;
        double lat1 = PI * (-0.5 + (double)i / lats);
        double z1 = sin(lat1) * r;
        double zr1 = cos(lat1) * r;

        
        for (j = 0; j <= longs; j++)
        {
            GLfloat lng = 2 * PI * (double)(j - 1) / longs;
            GLfloat x = cos(lng);
            GLfloat y = sin(lng);



            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
        }
        
   */ 
