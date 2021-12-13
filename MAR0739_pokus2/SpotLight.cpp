#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 amb, glm::vec3 diff, glm::vec3 spec, float constant, float linear, float quadratic, float cutOff, float outerCutOff) {
	this->ambient = amb;
	this->diffuse = diff;
	this->specular = spec;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
	this->cutOff = cutOff;
	this->outerCutOff = outerCutOff;
}
void SpotLight::setLightValuesToShader(int shaderProgram, Camera* camera) {
	int loc = glGetUniformLocation(shaderProgram, "spotLight.position");
	glUniform3fv(loc, 1, glm::value_ptr(camera->getCameraPos()));
	loc = glGetUniformLocation(shaderProgram, "spotLight.direction");
	glUniform3fv(loc, 1, glm::value_ptr(camera->getCameraFront()));
	loc = glGetUniformLocation(shaderProgram, "spotLight.ambient");
	glUniform3fv(loc, 1, glm::value_ptr(this->ambient));
	loc = glGetUniformLocation(shaderProgram, "spotLight.diffuse");
	glUniform3fv(loc, 1, glm::value_ptr(this->diffuse));
	loc = glGetUniformLocation(shaderProgram, "spotLight.specular");
	glUniform3fv(loc, 1, glm::value_ptr(this->specular));

	loc = glGetUniformLocation(shaderProgram, "spotLight.constant");
	glUniform1f(loc, this->constant);
	loc = glGetUniformLocation(shaderProgram, "spotLight.linear");
	glUniform1f(loc, this->linear);
	loc = glGetUniformLocation(shaderProgram, "spotLight.quadratic");
	glUniform1f(loc, this->quadratic);
	loc = glGetUniformLocation(shaderProgram, "spotLight.cutOff");
	glUniform1f(loc, this->cutOff);
	loc = glGetUniformLocation(shaderProgram, "spotLight.outerCutOff");
	glUniform1f(loc, this->outerCutOff);
}