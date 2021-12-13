#include "DirectionalLight.h"
DirectionalLight::DirectionalLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) {
	this->direction = dir;
	this->ambient = amb;
	this->diffuse = diff;
	this->specular = spec;
}
void DirectionalLight::setLightValuesToShader(int shaderProgram, Camera* camera) {
	int loc = glGetUniformLocation(shaderProgram, "dirLight.direction");
	glUniform3fv(loc, 1, glm::value_ptr(this->direction));
	loc = glGetUniformLocation(shaderProgram, "dirLight.ambient");
	glUniform3fv(loc, 1, glm::value_ptr(this->ambient));
	loc = glGetUniformLocation(shaderProgram, "dirLight.diffuse");
	glUniform3fv(loc, 1, glm::value_ptr(this->diffuse));
	loc = glGetUniformLocation(shaderProgram, "dirLight.specular");
	glUniform3fv(loc, 1, glm::value_ptr(this->specular));
}