#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include "ShaderProgram.h"
#include <iostream>
#include "ShaderProgram.h"
#include "ShaderProgramFactory.h"
#include "ShaderProgramType.h"
#include "Object.h"
#include "TextureController.h"
class ObjModelObject : public Object
{
public:
	ObjModelObject(const char* filename, ShaderProgramType shaderProgram, std::string textureName, bool loop = false, glm::mat4 defaultMat = glm::mat4(1.0f));
	void DrawObject(glm::mat4 view, glm::mat4 projection);

private:
	void loopModel();
	bool loop;
	float t = 0.5f;
	float delta = 0.01f;
	Vertex* points;
	GLuint IBO;
	unsigned int* indices;
	int num_of_faces;
	unsigned int indices_count;
	void getMaterialFromObj(aiScene* scene);
	void getMeshFromObj(const aiScene* scene);
	void InitIBO();
	int textureSpace; 
	glm::mat4 M = glm::mat4(1.0f);
	glm::mat4 A = glm::mat4(glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0));
	glm::mat4x3 B = glm::mat4x3(glm::vec3(-1, 0, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(1, 0, 0));
};