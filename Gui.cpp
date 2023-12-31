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
 
    ImGui::Checkbox("Render Light", &this->renderLight);

    if(ImGui::Button("Add Sphere")){
        object newMesh = object(1.0, 50, 50);
    }

    int length = Object.size();
    std::string title;

    for (int i = 0; i < length; i++) {

        

        Objects[i]->RenderLight(this->renderLight);
        

        title = "Object " + std::to_string(i + 1) + ":";
        ImGui::Text(title.c_str());

        //Color      

        title = " ";
        ImGui::ColorEdit3(title.c_str(), this->color);
        title = "Update Color" + std::to_string(i + 1);
        if (ImGui::Button(title.c_str())) {
            Objects[i]->SetColor(glm::vec3(color[0], color[1], color[2]));
        }
        //Works till this :

        
        title = " ";
        ImGui::ColorEdit3(title.c_str(), this->ambient);
        title = "Update Ambient" + std::to_string(i + 1);

        if (ImGui::Button(title.c_str())) {
            Objects[i]->SetAmbient(glm::vec3(ambient[0], ambient[1], ambient[2]));
        }
        //Diffuse
 
        title = " ";
        ImGui::ColorEdit3(title.c_str(), this->diffuse);
        title = "Update Diffuse" + std::to_string(i + 1);

        if (ImGui::Button(title.c_str())) {
            Objects[i]->SetDiffuse(glm::vec3(diffuse[0], diffuse[1], diffuse[2]));
        }
        //Specular
 
        title = " ";
        ImGui::ColorEdit3(title.c_str(), this->specular);
        title = "Update Specular" + std::to_string(i + 1);

        if (ImGui::Button(title.c_str())) {
            Objects[i]->SetSpecular(glm::vec3(specular[0], specular[1], specular[2]));
        }
        //Shininess
        title = " ";
        ImGui::SliderFloat(title.c_str(), this->shininess, 0.0f, 512.0f);
        title = "Update Shininess" + std::to_string(i + 1);

        if (ImGui::Button(title.c_str())) {
            Objects[i]->SetShininess(shininess[0]);
        }

    }
    length = DirLights.size();
    for (int i = 0; i < length; i++) {

        lightDirection[0] = DirLights[i].direction.x;
        lightDirection[1] = DirLights[i].direction.y;
        lightDirection[2] = DirLights[i].direction.z;

        title = "DirectionalLight Direction" + std::to_string(i + 1);
        ImGui::SliderFloat3(title.c_str(), this->lightDirection,-1,1);
        DirLights[i].direction = glm::vec3(lightDirection[0], lightDirection[1], lightDirection[2]);

        /*title = "Light Color" + std::to_string(i + 1);
        ImGui::ColorEdit3(title.c_str(), this->lightColor);
        PhongLights[i].lightColor = glm::vec3(lightColor[0], lightColor[1], lightColor[2]);*/
    }
    
    length = PointLights.size();
    for (int i = 0; i < length; i++) {

        lightPos[0] = PointLights[i].position.x;
        lightPos[1] = PointLights[i].position.y;
        lightPos[2] = PointLights[i].position.z;

        title = "PointLight Position" + std::to_string(i + 1);
        ImGui::SliderFloat3(title.c_str(), this->lightPos,-10,10);
        PointLights[i].position = glm::vec3(lightPos[0], lightPos[1], lightPos[2]);

        /*title = "Light Color" + std::to_string(i + 1);
        ImGui::ColorEdit3(title.c_str(), this->lightColor);
        PhongLights[i].lightColor = glm::vec3(lightColor[0], lightColor[1], lightColor[2]);*/
    }

    length = SpotLights.size();
    for (int i = 0; i < length; i++) {
            
        

        title = "SpotLight Position" + std::to_string(i + 1);
        ImGui::SliderFloat3(title.c_str(), this->lightPosSpot, -10, 10);

        //title = "SpotLight Position Update" + std::to_string(i + 1);
        //if (ImGui::Button(title.c_str())) {
            SpotLights[i].position = glm::vec3(lightPosSpot[0], lightPosSpot[1], lightPosSpot[2]);
        //}    

        title = "SpotLight Direction" + std::to_string(i + 1);
        ImGui::SliderFloat3(title.c_str(), this->lightDirectionSpot, -1, 1);

        //title = "SpotLight Direction Update" + std::to_string(i + 1);
        //if (ImGui::Button(title.c_str())) {
            SpotLights[i].direction = glm::vec3(lightDirectionSpot[0], lightDirectionSpot[1], lightDirectionSpot[2]);
        //}        
        
        title = "SpotLight CutOff Angle" + std::to_string(i + 1);
        ImGui::SliderFloat(title.c_str(), this->cutOff, 0.0f, 45.0f);

        //title = "SpotLight CutOff Angle Update" + std::to_string(i + 1);
        //if (ImGui::Button(title.c_str())) {
            //printf("We're here: "); std::cout << glm::cos(glm::radians(this->cutOff[0])) << std::endl;
            SpotLights[i].cutOff = glm::cos(glm::radians(this->cutOff[0]));
            SpotLights[i].outerCutOff = glm::cos(glm::radians(this->cutOff[0] + 2.5));
            //printf("SpotLight: "); std::cout << SpotLights[i].cutOff << std::endl;
        //}
            
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

