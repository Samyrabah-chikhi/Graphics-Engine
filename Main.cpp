#include <iostream>
#include <Windows.h>

#include "inclusion.h"

#define width 800
#define height 800


void Draw();
void Transformation(GLuint shader,glm::vec3 translation, glm::vec3 rotation, glm::vec3 scaling , const char* Unif, float angle);
void CameraTransformation(GLuint shader, glm::vec3 axis, glm::vec3 eye, glm::vec3 center, glm::vec3 up, float FOV, float minClip, float maxClip, float angle);
void Translate(GLuint shader, glm::vec3 translation, const char* Unif);
void Scale(GLuint shader, glm::vec3 scaling, const char* Unif);
void Rotate(GLuint shader, glm::vec3 rotation, float angle, const char* Unif);

int main() {

    GLFWwindow* window;
    OnCreate(&window,width,height);

    float vertices[] = {
        //Location          /Colors         //Texture map
        -0.5f,0.0f,0.5f,  0.7,0.6,0.5,     0.0f,0.0f,
        -0.5f,0.0f,-0.5f, 0.2f,0.7f,0.4f,  1.0f,0.0f,
        0.5f,0.0f,-0.5f,  0.1f,0.2f,0.8f,  0.0f,0.0f,
        0.5f,0.0f,0.5f,   0.5f,0.3f,0.1f,  1.0f,0.0f,
        0.0f,0.8f,0.0f,   0.9f,0.1f,0.1f,  0.5f,1.0f,
    };


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

    



    glEnable(GL_DEPTH_TEST);

    //Main loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);
        glBindTexture(GL_TEXTURE_2D, texture);

        glEnableVertexAttribArray(VAO);

        CameraTransformation(
            shader,
            glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec3(4.0f,3.0f,3.0f),
            glm::vec3(0.0f,0.0f,0.0f),
            glm::vec3(0.0f,1.0f,0.0f),
            45,
            0.1,
            100,
            90
        );






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



void CameraTransformation(GLuint shader,glm::vec3 axis,glm::vec3 eye,glm::vec3 center,glm::vec3 up,float FOV,float minClip,float maxClip,float angle) {

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(angle), axis);
    glm::mat4 view = glm::lookAt(
        eye,
        center,
        up
    );
    glm::mat4 projection = glm::perspective(glm::radians(FOV), (float)width / height, minClip, maxClip);

    glm::mat4 mvp = projection * view * model;

    GLuint matrixID = glGetUniformLocation(shader, "mvp");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
}
