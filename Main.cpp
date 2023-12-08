#include <iostream>
#include <Windows.h>

#include "Shader.h"
#include "CustomWindow.h"

void Draw();

int main() {

    float x = 0.0f;

    GLFWwindow* window;
    OnCreate(&window,800,800);

    //Vertex buffer and vertex array buffer
    GLuint VAO, VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Points to draw
    static const float points[]{
        0.0f,1.0f,0.0f,
        -1.0f,-1.0f,0.0f,
        1.0f,-1.0f,0.0f,
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
    //Loading shaders
	GLuint programID = LoadShaders(
        "E:\\Assets\\Vertex shader.txt",
        "E:\\Assets\\Fragment shader.txt"
    );

    //Main loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.0f, 0.0f, x, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //using shaders
		glUseProgram(programID);

        //interpreting how to use the data
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,                  //Must match the layout in the shader.
            3,                  // Dimension
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();

        x += 0.01;
        //Sleep(500);
        
    }

    OnDestroy(&VAO, &VBO, window);

    return 0;
}

void Draw() {


}