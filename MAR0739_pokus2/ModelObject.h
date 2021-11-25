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


#include "ShaderProgram.h"
#include <iostream>
#include "ShaderProgram.h"
#pragma once
class ModelObject
{
private:
	float* points;
	GLuint VAO = 0;
	int sizeOfPoints;
	ShaderProgram shaderProgram;
	void initObject(float* points, int sizeOfPoints, ShaderProgram shaderProgram);

public:
	ModelObject(float* points, int sizeOfPoints, ShaderProgram shaderProgram);
	ModelObject();
	void DrawObject(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
};

