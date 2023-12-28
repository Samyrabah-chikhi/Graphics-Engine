#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include "object.h"
#include "Light.h"

class Gui {

private:
	bool MoveCamera = false;
	bool renderLight = true;
	bool addCube = false;
	//Lights
	float lightDirection[3] = { -1.0f , 0.0f , -1.0f };
	float lightPos[3] = { 0.0f , 2.0f , 0.0f };

	float lightDirectionSpot[3] = { 0.0f, -1.0f, 0.0f };
	float lightPosSpot[3] = { 0.0f, 2.0f, 0.0f };

	float cutOff[1] = {12.0f};

	float lightColor[3] = { 1.0f , 1.0f , 1.0f };

	//Material
	float color[3] = { 1.0f , 1.0f , 1.0f };
	float ambient[3] = { 0.1f , 0.1f , 0.1f };
	float diffuse[3] = { 0.8f , 0.8f , 0.8f };;
	float specular[3] = { 1.0f, 1.0f, 1.0f };
	float shininess[1] = { 128.0f };

	
public:
	Gui(GLFWwindow* window);
	void BeforeDrawing();
	void AfterDrawing(std::vector<object*> Object);
	void Render();
	void Destroy();
	bool getMoveCamera();
	ImGuiIO* io;

	
};