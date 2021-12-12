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

#include <SOIL.h>

#include "ModelObject.h"
#include "ShaderProgramType.h"
#include "Camera.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <stdlib.h>

class TextureController
{
private:
	TextureController();
	int availableTexture = 33984;
	int textureCount = 0;
	std::map<std::string, int> loadedTextures;
	static TextureController* instance;
public:
	static TextureController* getInstance() {
		if (!instance)
			instance = new TextureController;
		return instance;
	}
	void loadNewTexture(ShaderProgramType shaderType, std::string name, std::string path = "");
	int getTextureByName(std::string name);
};
