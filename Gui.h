#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include "object.h"

class Gui {

private:
	bool MoveCamera = false;
	float color[3] = { 1.0f , 1.0f , 1.0f};
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