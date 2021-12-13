#include "Light.h"
Light::Light(glm::vec3 pos, float shininess) {
	this->position = pos;
	this->shininess = shininess;
}
void Light::setLightValuesToShader(int shaderProgram, Camera* camera) {
    int projectionLoc = glGetUniformLocation(shaderProgram, "viewPos");
    glUniform3fv(projectionLoc, 1, glm::value_ptr(camera->getCameraPos()));
    GLint uniformID = glGetUniformLocation(shaderProgram, "material.shininess");
    glUniform1f(uniformID, shininess);
}