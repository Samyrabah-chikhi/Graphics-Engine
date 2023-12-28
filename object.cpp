#include "object.h"

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 Normal;
out mat4 mvp;
void main()
	{
		gl_Position = vec4(aPos, 1.0);

		FragPos = gl_Position.xyz;
		Normal = aNormal;
		mvp = projection * view * model;
}
)";
const char* geomtryShaderSource = R"(
#version 330 core
layout(triangles) in;
layout(triangle_strip,max_vertices = 3) out ;

in mat4 mvp[];
in vec3 Normal[];

out vec3 Normals;
void main(){

	 for(int i = 0; i < 3; i++)
    {	
		Normals = Normal[i];
        gl_Position = mvp[i]*gl_in[i].gl_Position;
        EmitVertex();
		
    }
    EndPrimitive();
}

)";


const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

in vec3 Normals;
in vec3 FragPos;

struct Material {
    vec3 color;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

struct PointLight {    
    vec3 position;
	
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct SpotLight {
    vec3 position;  
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
};

#define NR_POINT_LIGHTS 16
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int nbrPointLight;

#define NR_DIR_LIGHTS 16
uniform DirLight dirLights[ NR_DIR_LIGHTS];
uniform int nbrDirLight;

#define NR_SPOT_LIGHTS 16
uniform SpotLight spotLights[ NR_SPOT_LIGHTS];
uniform int nbrSpotLight;


uniform vec3 viewPos;
uniform Material material;

uniform bool lightExist;

vec3 calcSpotLight(SpotLight light,vec3 norm, vec3 FragPos , vec3 viewDir){

    vec3 ambient = light.ambient * material.diffuse;
    
    // diffuse 
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * material.diffuse;  
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * material.specular;  
    
    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    return ambient + diffuse + specular;

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light.ambient  * material.diffuse;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    return (ambient + diffuse + specular);
} 

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    

    vec3 ambient  = light.ambient  * material.diffuse;
    vec3 diffuse  = light.diffuse  * diff * material.diffuse;
    vec3 specular = light.specular * spec * material.specular;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 


void main()
{    

  if(lightExist){
		
  	vec3 result = vec3(0.0);

	vec3 norm = normalize(Normals);
	vec3 viewDir = normalize(viewPos - FragPos);

	for(int i = 0; i < nbrDirLight; i++)
		result += CalcDirLight(dirLights[i], norm,viewDir );
	
    for(int i = 0; i < nbrPointLight; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir); 
	
	for(int i = 0; i < nbrSpotLight; i++)
		result += calcSpotLight(spotLights[i], norm, FragPos, viewDir);
	
    FragColor = vec4(result*material.color, 1.0);

}
	else{
    FragColor = vec4(material.color, 1.0);
}

}
)";

float cubeMesh[] = {

			0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f ,
			0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f ,

			1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f ,
			1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f ,

			1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f ,
			1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f ,

			0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f ,
			0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f ,

			0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f ,
			0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f ,

			1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f ,
			1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f ,

};

//std::vector<PhongLight> light;

std::vector<object*> Objects;

int object::numberOfObjects = 0;

object::object() {

	this->indexExist = false;
	this->shaderExist = false;
	this->textureExist = false;
	this->materialExist = false;

	this->material.color = glm::vec3(1.0f, 0.0f, 0.0f);
	this->material.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	this->material.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	this->material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->material.shininess = 128.0f;

	this->indexOfObject = numberOfObjects;

	Objects.push_back(this);
	numberOfObjects++;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);



	for (int i = 0; i < sizeof(cubeMesh)/sizeof(float); i++) {
		this->vertex.push_back(cubeMesh[i]);
	}

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertex.size(), this->vertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	this->calculateNormals();

	CreateShader();
}

object::object(float* vertices) {
	this->indexExist = false;
	this->shaderExist = false;
	this->textureExist = false;
	this->materialExist = false;

	this->material.color = glm::vec3(1.0f, 0.0f, 0.0f);
	this->material.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	this->material.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	this->material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->material.shininess = 128.0f;

	this->indexOfObject = numberOfObjects;

	Objects.push_back(this);
	numberOfObjects++;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	int numberOfVertices = sizeof(vertices) / sizeof(float);

	for (int i = 0; i < numberOfVertices; i++) {
		this->vertex.push_back(vertices[i]);
	}

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertex.size(), this->vertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	this->calculateNormals();

	CreateShader();
}

object::object(float* vertices, glm::vec3 origin) {

	this->indexExist = false;
	this->shaderExist = false;
	this->textureExist = false;
	this->materialExist = false;

	this->material.color = glm::vec3(1.0f, 0.0f, 0.0f);
	this->material.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	this->material.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	this->material.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	this->material.shininess = 128.0f;

	this->indexOfObject = numberOfObjects;

	Objects.push_back(this);
	numberOfObjects++;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	int numberOfVertices = sizeof(vertices) / sizeof(float);

	for (int i = 0; i < numberOfVertices; i += 3) {
		this->vertex.push_back(vertices[i] + origin.x);
		this->vertex.push_back(vertices[i + 1] + origin.y);
		this->vertex.push_back(vertices[i + 2] + origin.z);
	}

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertex.size(), this->vertex.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	this->calculateNormals();

	CreateShader();
}

object::object(float* vertices, glm::vec3 origin, glm::vec3 customColor) :
	object::object(vertices, origin) {
	this->material.color = customColor;
}

object::object(float* vertices, int* indices, int numberOfIndices, glm::vec3 origin) :
	object::object(vertices, origin) {

	this->indexExist = true;
	for (int i = 0; i < numberOfIndices; i++)
		this->indices.push_back(indices[i]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);

}

void object::AddShader(float* colors, int numberOfColors) {


	//Dont forget to change AttribPointer to skip by 6 in both the layouts
	this->shaderExist = true;
	for (int i = 0; i < numberOfColors; i++)
		this->colors.push_back(colors[i]);
	glGenBuffers(1, &this->VBOColor);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBOColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->colors.size(), this->colors.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	//Not finished , we have to change the vertex and fragment files

}

void object::Render(glm::mat4* mvp) {
	glBindVertexArray(this->VAO);
	glUseProgram(this->shaderID);

	glUniform3f(glGetUniformLocation(this->shaderID, "material.color"),
		this->material.color.x, this->material.color.y, this->material.color.z);

	glUniform3f(glGetUniformLocation(this->shaderID, "material.ambient"),
		this->material.ambient.x, this->material.ambient.y, this->material.ambient.z);

	glUniform3f(glGetUniformLocation(this->shaderID, "material.specular"),
		this->material.specular.x, this->material.specular.y, this->material.specular.z);

	glUniform3f(glGetUniformLocation(this->shaderID, "material.diffuse"),
		this->material.diffuse.x, this->material.diffuse.y, this->material.diffuse.z);

	glUniform1f(glGetUniformLocation(this->shaderID, "material.shininess"),
		this->material.shininess);

	if (!this->renderLight) {
		glUniform1f(glGetUniformLocation(this->shaderID, "lightExist"),
			false);

	}
	else {

	}


	// un truc du genre , rendering light will stay optional
	// set to false unless there's light
	// button to desactive light and one to reactivate it 
		
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (this->textureExist)
		glUseProgram(this->TextureID);
	if (this->indexExist) {
		glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, this->vertex.size());
	}

	ProjectMesh(mvp);
}

void object::translate(glm::vec3 translation)
{
}
void object::rotate(glm::vec3 rotation, float angle)
{
}
void object::scale(glm::vec3 scale)
{
}

void object::CreateShader() {

	std::string indexOfobject = std::to_string(this->indexOfObject);

	std::string geomtryFileName = "E:\\Assets\\Geomtry shader" + indexOfobject + ".txt";
	std::string vertexFileName = "E:\\Assets\\Vertex shader" + indexOfobject + ".txt";
	std::string fragmentFileName = "E:\\Assets\\Fragment shader" + indexOfobject + ".txt";

	FILE* fptr = nullptr;
	if (fopen_s(&fptr, vertexFileName.c_str(), "w") != 0) {
		printf("Problem in opening the vertex shader file\n");
		exit(1);
	}
	fwrite(vertexShaderSource, sizeof(char), strlen(vertexShaderSource), fptr);
	fclose(fptr);

	if (fopen_s(&fptr, fragmentFileName.c_str(), "w") != 0) {
		printf("Problem in opening the fragment shader file\n");
		exit(1);
	}
	fwrite(fragmentShaderSource, sizeof(char), strlen(fragmentShaderSource), fptr);
	fclose(fptr);

	if (fopen_s(&fptr, geomtryFileName.c_str(), "w") != 0) {
		printf("Problem in opening the goemtry shader file\n");
		exit(1);
	}
	fwrite(geomtryShaderSource, sizeof(char), strlen(geomtryShaderSource), fptr);
	fclose(fptr);

	this->shaderID = LoadShaders(vertexFileName.c_str(), fragmentFileName.c_str(), geomtryFileName.c_str());
}

GLuint object::LoadShaders(const char* vertex_file_path, const char* fragment_file_path, const char* geomtry_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLuint GeomtryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}
	// Read The Geomtry Shader code from the file
	std::string GeomtryShaderCode;
	std::ifstream GeomtryShaderStream(geomtry_file_path, std::ios::in);
	if (GeomtryShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << GeomtryShaderStream.rdbuf();
		GeomtryShaderCode = sstr.str();
		GeomtryShaderStream.close();
	}


	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Compile Geomtry Shader
	printf("Compiling shader : %s\n", geomtry_file_path);
	char const* GeomtrySourcePointer = GeomtryShaderCode.c_str();
	glShaderSource(GeomtryShaderID, 1, &GeomtrySourcePointer, NULL);
	glCompileShader(GeomtryShaderID);

	// Check Geomtry Shader
	glGetShaderiv(GeomtryShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(GeomtryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> GeomtryShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(GeomtryShaderID, InfoLogLength, NULL, &GeomtryShaderErrorMessage[0]);
		printf("%s\n", &GeomtryShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ID = glCreateProgram();
	glAttachShader(ID, VertexShaderID);
	glAttachShader(ID, FragmentShaderID);
	glAttachShader(ID, GeomtryShaderID);

	glLinkProgram(ID);

	// Check the program
	glGetProgramiv(ID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ID, VertexShaderID);
	glDetachShader(ID, FragmentShaderID);
	glDetachShader(ID, GeomtryShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glDeleteShader(GeomtryShaderID);

	return ID;
}

void object::ProjectMesh(glm::mat4* mvp) {

	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "model"), 1, GL_FALSE, &mvp[0][0][0]);
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "view"), 1, GL_FALSE, &mvp[1][0][0]);
	glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "projection"), 1, GL_FALSE, &mvp[2][0][0]);

}
void object::setLightExist(bool setLight)
{
	this->lightExist = setLight;
}


void object::calculateNormals() {

	this->VBONormals;
	glBindVertexArray(this->VAO);
	glGenBuffers(1, &this->VBONormals);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBONormals);

	glm::vec3 norm;
	glm::vec3 edge1, edge2;
	int points = this->vertex.size() / 3;
	printf("Number of points : %d\n", points);

	for (int i = 0; i < points; i+=3) {
		//printf("[%d]\n", i);
		edge1 = this->point(i + 1) - this->point(i + 0);
		edge2 = this->point(i + 2) - this->point(i + 0);
		norm = glm::cross(edge1, edge2);

		for (int j = 0; j < 3; j++) {
			this->normals.push_back(norm.x);
			this->normals.push_back(norm.y);
			this->normals.push_back(norm.z);
		}
			

	}
	printf("Length of normal coordinates: %d\n", this->normals.size());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->normals.size(), this->normals.data(),GL_STATIC_DRAW);	
	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

}
void object::SetViewPos(glm::vec3 camPos)
{
	glUniform3fv(glGetUniformLocation(this->shaderID, "viewPos"),
		1.0f, glm::value_ptr(camPos));
}

void object::SetColor(glm::vec3 color)
{
	this->material.color = color;
}
void object::SetAmbient(glm::vec3 ambient)
{
	this->material.ambient.x = ambient.x;
	this->material.ambient.y = ambient.y;
	this->material.ambient.z = ambient.z;
}
void object::SetDiffuse(glm::vec3 diffuse)
{
	this->material.diffuse.x = diffuse.x;
	this->material.diffuse.y = diffuse.y;
	this->material.diffuse.z = diffuse.z;
}
void object::SetSpecular(glm::vec3 specular)
{
	this->material.specular.x = specular.x;
	this->material.specular.y = specular.y;
	this->material.specular.z = specular.z;	
}
void object::SetShininess(float shininess)
{
	this->material.shininess = shininess;
}

glm::vec3 object::point(int index) {
	return glm::vec3(this->vertex[3 * index], this->vertex[3 * index + 1], this->vertex[3 * index + 2]);
}

void generateSphere(float radius, int stackCount, int sectorCount) {
	
}
GLuint object::GetShaderID() {
	return this->shaderID;
}

void object::RenderLight(bool renderLight) {
	this->renderLight = renderLight;
}

