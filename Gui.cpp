#include "Gui.h"

Gui::Gui(GLFWwindow* window) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->io = &ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


}

void Gui::BeforeDrawing()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::AfterDrawing(std::vector<object*> Object)
{
    ImGui::Begin("User Interface");

    int length = Object.size();

    bool* setColors = (bool*)malloc(length*sizeof(bool));
    bool* setAmbients = (bool*)malloc(length * sizeof(bool));
    bool* setDiffuses = (bool*)malloc(length * sizeof(bool));
    bool* setSpeculars = (bool*)malloc(length * sizeof(bool));
    bool* setShininesses = (bool*)malloc(length * sizeof(bool));

    for (int i = 0; i < length; i++) {
        
        setColors[i] = false;
        setAmbients[i] = false;
        setDiffuses[i] = false;
        setSpeculars[i] = false;
        setShininesses[i] = false;

        std::string title = "Object " + std::to_string(i + 1) + ":";
        ImGui::Text(title.c_str());

        //Color

        title = " Set Color ";
        ImGui::ColorEdit3(title.c_str(), this->color);
        title = "Update Color";
        ImGui::Checkbox(title.c_str(), &setColors[i]);
     
        if (setColors[i]) {
            Objects[i]->SetColor(glm::vec3(color[0], color[1], color[2]));
        }
        //Works till this :

        //Ambient
        
        title = " Set Ambient ";
        ImGui::ColorEdit3(title.c_str(), this->ambient);
        title = "Update Ambient";
        ImGui::Checkbox(title.c_str(), &setAmbients[i]);

        if (setAmbients[i]) {
            Objects[i]->SetAmbient(glm::vec3(ambient[0], ambient[1], ambient[2]));
        }
        //Diffuse
 
        title = " Set Diffuse ";
        ImGui::ColorEdit3(title.c_str(), this->diffuse);
        title = "Update Diffuse";
        ImGui::Checkbox(title.c_str(), &setDiffuses[i]);

        if (setDiffuses[i]) {
            Objects[i]->SetDiffuse(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));
        }
        //Specular
 
        title = " Set Specular ";
        ImGui::ColorEdit3(title.c_str(), this->specular);
        title = "Update Specular";
        ImGui::Checkbox(title.c_str(), &setSpeculars[i]);

        if (setSpeculars[i]) {
            Objects[i]->SetSpecular(glm::vec3(specular[0], specular[1], specular[2]));
        }
        //Shininess
        title = " Set Shininess ";
        ImGui::SliderFloat(title.c_str(), this->shininess, 0.0f, 512.0f);
        title = "Update Shininess";
        ImGui::Checkbox(title.c_str(), &setShininesses[i]);
        if (setShininesses[i]) {
            Objects[i]->SetShininess(shininess[0]);
        }
    }
    ImGui::End();
}

void Gui::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
}

bool Gui::getMoveCamera()
{
    return this->MoveCamera;
}

