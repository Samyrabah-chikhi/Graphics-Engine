#include "inclusion.h"

#define width 800
#define height 800

void Translate(GLuint shader, glm::vec3 translation);
void Scale(GLuint shader, glm::vec3 scaling);
void Rotate(GLuint shader, glm::vec3 rotationDir, float angle);

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

    object pp = object(cubeMesh,sizeof(cubeMesh)/sizeof(float));
    object popa = object(
        cubeMesh, 
        sizeof(cubeMesh) / sizeof(float), 
        glm::vec3(-2.0f, 0.0f, 0.0f)
        ,glm::vec3(1.0f,0.0f,0.0f)
    );

    glm::vec3 customColor(0.47, 0.52, 0.12);

    
    //Light
    GLuint VAOLight, VBOLight;
    glGenVertexArrays(1, &VAOLight);
    glGenBuffers(1, &VBOLight);

    glBindVertexArray(VAOLight);  
    glBindBuffer(GL_ARRAY_BUFFER, VBOLight);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint lightShader = LoadShader(
        "E:\\Assets\\Vs.txt",
        "E:\\Assets\\Fs.txt"
    );
   

    //Camera things

    glEnable(GL_DEPTH_TEST);

    float rotation = 0.0f;
    float prevTime = glfwGetTime(),crntTime;
    
    //Make a struct containing all 


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

    Camera cam = Camera(window,position,orientation,up,width,height,initialFoV);

    //Main loop
    while (!glfwWindowShouldClose(window)) {

        glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        

        InitCamera(&mvp, position, orientation, up, initialFoV, 0.1, 100);
        cam.render(Objects); 

        float crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1 / 60) {
            cam.CameraMove(window);
            cam.TransformCamera();

            prevTime = crntTime;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
       
        
    }

    OnDestroy(&VAOLight, &VBOLight, window);

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
