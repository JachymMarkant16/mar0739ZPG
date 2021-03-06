#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
private:
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
public:
	DirectionalLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec);
	void setLightValuesToShader(int shaderProgram, Camera* camera);
};

