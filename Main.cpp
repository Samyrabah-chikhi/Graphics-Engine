#include <iostream>
#include <Windows.h>

#include "inclusion.h"
#include "Shader.h"
#include "CustomWindow.h"

void Draw();

int main() {

    glm::mat4 lmao;

    float x = 0.0f;

    GLFWwindow* window;
    OnCreate(&window,800,800);



    //Vertex buffer and vertex array buffer
    GLuint VAO,VAO_,VBO_, VBO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Points to draw
    float points[] = {
        0.0f,  0.0f, 0.0f,  
        0.0f, 0.5f, 0.0f,  
        -0.5f, 0.0f, 0.0f,   
    };
    unsigned int indices[]{
        0,1,2,
        0,1,3
    };

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /*unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/


    //Loading shaders
	GLuint programID = LoadShaders(
        "E:\\Assets\\Vertex shader.txt",
        "E:\\Assets\\Fragment shader.txt"
    );

    float vertex[]{
        0.0f,0.0f,0.0f,
        0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f
    };

    glGenVertexArrays(1, &VAO_);
    glBindVertexArray(VAO_);

    glGenBuffers(1, &VBO_);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	 
    glEnableVertexAttribArray(0);


    GLuint shader2 = LoadShaders(
        "E:\\Assets\\Vertex shader.txt",
        "E:\\Assets\\Fragment shader2.txt"
    );
    
    //Main loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0, 0.3f, x, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //using shaders
		glUseProgram(programID);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // Draw the triangle !
        glLineWidth(2.0f);

        glBindVertexArray(1);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        float time = glfwGetTime();
        float greenValue = (sin(time) / 2.0f) + 0.5f;
        int vertexColorlocation = glGetUniformLocation(shader2, "ourColor");
        glUseProgram(shader2);
        glUniform4f(vertexColorlocation, 1.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES,6, GL_UNSIGNED_INT, 0);
        //glDisableVertexAttribArray(0);


        glfwSwapBuffers(window);
        glfwPollEvents();

        x += 0.001;
        //Sleep(50);
        
    }
    glDeleteVertexArrays(1, &VAO_);
    glDeleteBuffers(1, &VBO_);
        
    OnDestroy(&VAO, &VBO, window);

    return 0;
}

void Draw() {


}