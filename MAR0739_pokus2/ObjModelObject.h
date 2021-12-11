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
#include "Texture2D.h"
class ObjModelObject : public Object
{
public:
	ObjModelObject(const char* filename);
	Texture2D texture;

private:
	Vertex* points;
	GLuint IBO;
	unsigned int* indices;
	int num_of_faces;
	unsigned int indices_count;
	void getMaterialFromObj(aiScene* scene);
	void getMeshFromObj(const aiScene* scene);
};