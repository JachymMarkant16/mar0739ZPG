#include "PointLight.h"


PointLight::PointLight(glm::vec3 pos, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic, int order) {
	this->position = pos;
	this->ambient = amb;
	this->diffuse = diff;
	this->specular = spec;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->order = order;
}
void PointLight::setLightValuesToShader(int shaderProgram, Camera* camera) {
	int loc = glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(order) +"].position").c_str());
	glUniform3fv(loc, 1, glm::value_ptr(this->position));
	loc = glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(order) + "].ambient").c_str());
	glUniform3fv(loc, 1, glm::value_ptr(this->ambient));
	loc = glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(order) + "].diffuse").c_str());
	glUniform3fv(loc, 1, glm::value_ptr(this->diffuse));
	loc = glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(order) + "].specular").c_str());
	glUniform3fv(loc, 1, glm::value_ptr(this->specular));
	loc = glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(order) + "].constant").c_str());
	glUniform1f(loc, this->constant);
	loc = glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(order) + "].linear").c_str());
	glUniform1f(loc, this->linear);
	loc = glGetUniformLocation(shaderProgram, ("pointLights[" + std::to_string(order) + "].quadratic").c_str());
	glUniform1f(loc, this->quadratic);
}