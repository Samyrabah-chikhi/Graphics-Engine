#include <iostream>
#include <Windows.h>

#include "inclusion.h"
#include "Shader.h"
#include "CustomWindow.h"

void Draw();
    
int main() {

    glm::mat4 lmao;

    float x = 0.0f,z=0.0f,y=0.0f;

    GLFWwindow* window;
    OnCreate(&window,800,800);


    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Loading shaders
	GLuint programID = LoadShaders(
        "E:\\Assets\\Vertex shader.txt",
        "E:\\Assets\\Fragment shader.txt"
    );



    float vertex[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint shader2 = LoadShaders(
        "E:\\Assets\\Vertex shader.txt",
        "E:\\Assets\\Fragment shader2.txt"
    );
    
    //Main loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0, 0.3f, 0.2, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //using shaders
		glUseProgram(shader2);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        
        //Draw 
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();

        x += 0.01;
        if (x > 1) {
            x = 0;
        }
        z += 0.1;
        y += 0.05;
        //Sleep(50);
        
    }

    OnDestroy(&VAO, &VBO, window);

    return 0;
}

void Draw() {


}