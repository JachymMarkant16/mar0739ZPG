#pragma once
#include "Light.h"
class PointLight :
    public Light
{
protected:
    glm::vec3 position;
    float attenuation_constant;
    float attenuation_linear;
    float attenuation_quadratic; 
public:
        PointLight(glm::vec3 color_of_light, glm::vec3 position, float c, float l, float q);
        ~PointLight();
        void set_position(glm::vec3 position);
        virtual void update() override;
};

