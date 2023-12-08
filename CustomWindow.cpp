#include "CustomWindow.h"

void OnCreate(GLFWwindow** window,int width,int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    CreatingWindow(window,width,height);
}


void OnDestroy(GLuint* VAO, GLuint* VBO, GLFWwindow* window) {

    glDeleteVertexArrays(1, VAO);
    glDeleteBuffers(1, VBO);


    glfwDestroyWindow(window);
    glfwTerminate();

}
void CreatingWindow(GLFWwindow** window,int width,int height) {
    *window = glfwCreateWindow(width, height, "Graphics Engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }

    //Making the window the current context
    glfwMakeContextCurrent(*window);

    //Glad init
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    //Where openGL operates
    glViewport(0, 0, width, height);

}