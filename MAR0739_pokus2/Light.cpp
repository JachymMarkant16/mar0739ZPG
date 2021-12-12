#include "Light.h"
Light::Light(glm::vec3 color_of_light) {
	this->lightColor = color_of_light;
	////to shader
	//set_changed_values(this->color_of_light, "lights[" + ss.str() + "].color_of_light");
	//set_changed_values(BaseLight::count_of_lights + 1, "numOfLights");
}
void Light::setLightColor(glm::vec3 lightColor) {
	this->lightColor = lightColor;
}