#include "object.h"



int object::numberOfObjects = 0;
std::vector<object> object::Object;


	object::object(float* vertices, int numberOfVertices) {

		indexExist = false;
		shaderExist = false;
		textureExit = false;

		Object.push_back(*this);
		numberOfObjects++;

		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);

		for (int i = 0; i < numberOfVertices; i++)
			this->vertex.push_back(vertices[i]);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



		glBindVertexArray(this->VAO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->vertex.size(), this->vertex.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		CreateShader();
	}

	object::object(float* vertices, int numberOfVertices, int* indices, int numberOfIndices) :
		object(vertices, numberOfVertices) {

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
		glUseProgram(this->shaderID);
		if (this->textureExit)
			glUseProgram(this->TextureID);
		glBindVertexArray(this->VAO);
		if (indexExist) {
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
		}
		//printf("%d", this->vertex.size());
		glDrawArrays(GL_TRIANGLES, 0, this->vertex.size());

		ProjectMesh(mvp);
	}
	void object::CreateShader() {

		std::string indexOfobject = std::to_string(this->indexOfObject);

		const char* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 aPos;\n"
			"uniform mat4 model;\n"
			"uniform mat4 view;\n"
			"uniform mat4 projection;\n"
			"void main()\n"
			"{\n"
			"  gl_Position = projection * view * model * vec4(aPos+vec3(2.0,0.0f,0.0f), 1.0);\n"
			"}\0";
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"FragColor = vec4(0.6f, 0.6f, 0.6f, 1.0f);\n"
			"}\0";

		std::string vertexFileName = "E:\\Assets\\vertexShader" + indexOfobject + ".txt";
		std::string fragmentFileName = "E:\\Assets\\fragmentShader" + indexOfobject + ".txt";

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

		this->shaderID = LoadShaders(vertexFileName.c_str(), fragmentFileName.c_str());
	}

	GLuint object::LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

		// Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << VertexShaderStream.rdbuf();
			VertexShaderCode = sstr.str();
			VertexShaderStream.close();
		}
		else {
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
			getchar();
			return 0;
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

		// Link the program
		printf("Linking program\n");
		GLuint ID = glCreateProgram();
		glAttachShader(ID, VertexShaderID);
		glAttachShader(ID, FragmentShaderID);
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

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);

		return ID;
	}

	void object::ProjectMesh(glm::mat4* mvp) {

		glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "model"), 1, GL_FALSE, &mvp[0][0][0]);
		glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "view"), 1, GL_FALSE, &mvp[1][0][0]);
		glUniformMatrix4fv(glGetUniformLocation(this->shaderID, "projection"), 1, GL_FALSE, &mvp[2][0][0]);
	}
	



