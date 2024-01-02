#include "inclusion.h"

#define width 1080
#define height 1080

int main() {
      
    //Window creation

    GLFWwindow* window;
    OnCreate(&window,width,height);
   
    Gui userInterface = Gui(window);
        
    //float cubeMesh[] = {

    //    0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f ,
    //    0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f ,

    //    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f ,
    //    1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f ,

    //    1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f ,
    //    1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f ,

    //    0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f ,
    //    0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f ,

    //    0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f ,
    //    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f ,

    //    1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f ,
    //    1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f ,

    //};

    //Objects creation


    object popa = object(1.0,50,50);
    //object pop = object(cubeMesh, glm::vec3(0, 3, -1),glm::vec3(1,1,0));
    //Make a struct containing all camera settings

    glm::vec3 position= glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 orientation= glm::vec3(0.0f, 0.0f, -1.0f);

    Camera cam = Camera(window,position,orientation);

    //addLight(DIRECTIONAL_LIGHT);
    //addLight(POINT_LIGHT);
    addLight(SPOT_LIGHT);

    //Main Loop and framerate
    int nbFrames = 0;
    float prevTime = glfwGetTime(), crntTime;

   // printf("Number of objects : %d\n", Objects.size());

    //Main loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        userInterface.BeforeDrawing();

        cam.render(Objects); 

        userInterface.AfterDrawing(Objects);
        userInterface.Render();


        float crntTime = glfwGetTime();

        if (crntTime - prevTime >= 1 / 60) {

            if (!userInterface.io->WantCaptureMouse) {
                cam.CameraMove(window);
                cam.TransformCamera();
            }
            
            prevTime = crntTime;
        }



        glfwSwapBuffers(window);
        glfwPollEvents();
       
        
    }
    userInterface.Destroy();
    OnDestroy(NULL,NULL, window);

    return 0;
}

