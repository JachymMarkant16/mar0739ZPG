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
#include <string>
class ModelObject : public Object
{
private:
	bool isSkybox;
	float* points;
	int textureSpace;

public:
	ModelObject(float* points, int sizeOfPoints, ShaderProgramType shaderProgram, std::string textureName, bool isSkybox = false);
	ModelObject();
	void DrawObject(glm::mat4 view, glm::mat4 projection);
};

