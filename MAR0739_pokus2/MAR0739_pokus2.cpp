//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include <iostream>
#include "ModelObject.h"
#include "Core.h"
#include "gift.h"
#include "plain.h"
#include "box.h"
#include "sphere.h"
#include "box2.h"
#include "skybox.h"
#include "TextureController.h"
#include "ObjModelObject.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

float points[] = {
    // positions         // colors
     0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,    // top 
    // positions         // colors
     0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
};

Core* Core::instance = 0;
TextureController* TextureController::instance = 0;

int main()
{
    Core* core = core->getInstance();
    core->setData(800, 600, "ZPG");
    core->initCore();

    TextureController* textController = textController->getInstance();
    textController->loadNewTexture(ShaderProgramType::SkyBox, "skybox");
    textController->loadNewTexture(ShaderProgramType::TwoD, "box", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\svetlo.png");
    textController->loadNewTexture(ShaderProgramType::ThreeDPhong, "house", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\house.png");
    textController->loadNewTexture(ShaderProgramType::ThreeD, "zombie", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\zombie.png");
    textController->loadNewTexture(ShaderProgramType::ThreeDPhong, "tree", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\tree.png");
    textController->loadNewTexture(ShaderProgramType::ThreeDPhong, "teren", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\teren.png");
    
    glm::vec3 lightPos1 = glm::vec3(30.0f,100.0f, 35.0f);
    glm::vec3 lightPos2 = glm::vec3(-15.0f,10.0f,-20.0f);

    std::vector<Light*> lights;
    lights.push_back(new Light(glm::vec3(1.0), 32.0f));
    lights.push_back(new DirectionalLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f)));
    lights.push_back(new PointLight(lightPos1, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(300.0f, 300.0f, 300.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.032f, 0));
    lights.push_back(new PointLight(lightPos2, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.0f, 0.032f, 1));
    lights.push_back(new SpotLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f))));

    
    ModelObject *skybox = new ModelObject(box, sizeof(box), ShaderProgramType::SkyBox, "skybox", true);
    glm::mat4 L1 = glm::mat4(1.0f);
    L1 = glm::translate(L1, lightPos1);
    L1 = glm::scale(L1, glm::vec3(0.5, 0.5, 0.5));
    ModelObject *svetlo1 = new ModelObject(box, sizeof(box), ShaderProgramType::TwoD, "box", false, L1);
    glm::mat4 L2 = glm::mat4(1.0f);
    L2 = glm::translate(L2, lightPos2);
    L2 = glm::scale(L2, glm::vec3(0.5, 0.5, 0.5));
    ModelObject* svetlo2 = new ModelObject(box, sizeof(box), ShaderProgramType::TwoD, "box",false,  L2);
    ObjModelObject *house = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\house.obj", ShaderProgramType::ThreeDPhong, "house");
    house->setLights(lights);
    ObjModelObject* zombie = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\zombie.obj", ShaderProgramType::ThreeDPhong, "zombie", true);
    zombie->setLights(lights);
    glm::mat4 Z2 = glm::mat4(1.0f);
    Z2 = glm::translate(Z2, glm::vec3(2.0f, 0.0f, 10.0f));
    ObjModelObject* zombie2 = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\zombie.obj", ShaderProgramType::ThreeDPhong, "zombie", false, Z2);
    zombie2->setLights(lights);
    //ObjModelObject* tree = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\tree.obj", ShaderProgramType::ThreeDPhong, "tree");
    //tree->setLights(lights);
    ObjModelObject* teren = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\teren.obj", ShaderProgramType::ThreeDPhong, "teren");
    teren->setLights(lights);
    core->addObject(skybox);
    core->addObject(teren);
    core->addObject(svetlo1);
    core->addObject(svetlo2);
    core->addObject(house);
    core->addObject(zombie);
    core->addObject(zombie2);
    core->start();
}
