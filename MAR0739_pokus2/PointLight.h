#pragma once
#include "Light.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <string.h>

class PointLight : public Light
{
private:
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	float constant;
	float linear;
	float quadratic;
	int order;
public:
	PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic, int order);
	void setLightValuesToShader(int shaderProgram, Camera* camera);
};

