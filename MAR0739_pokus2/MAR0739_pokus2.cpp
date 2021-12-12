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
#include "box2.h"
#include "skybox.h"
#include "TextureController.h"
#include "ObjModelObject.h"

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
    //textController->loadNewTexture(ShaderProgramType::TwoD, "box", "..\\..\\Textures\\box.png");
    textController->loadNewTexture(ShaderProgramType::ThreeD, "house", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\house.png");
    textController->loadNewTexture(ShaderProgramType::ThreeD, "zombie", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\zombie.png");
    textController->loadNewTexture(ShaderProgramType::ThreeD, "tree", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\tree.png");
    textController->loadNewTexture(ShaderProgramType::ThreeD, "teren", "C:\\Skola\\ZPG\\mar_pokus2\\Textures\\teren.png");

    
    ModelObject *skybox = new ModelObject(box, sizeof(box), ShaderProgramType::SkyBox, "skybox", true);
    //ModelObject *boxik = new ModelObject(box, sizeof(box), ShaderProgramType::TwoD, "box");
    //ModelObject* boxik2 = new ModelObject(box, sizeof(box), ShaderProgramType::TwoD, "box");
    ObjModelObject *house = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\house.obj", ShaderProgramType::ThreeD, "house");
    ObjModelObject* zombie = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\zombie.obj", ShaderProgramType::ThreeD, "zombie");
    ObjModelObject* tree = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\tree.obj", ShaderProgramType::ThreeD, "tree", true);
    ObjModelObject* teren = new ObjModelObject("C:\\Skola\\ZPG\\mar_pokus2\\Objects\\plane.obj", ShaderProgramType::ThreeD, "teren");
    core->addObject(skybox);
    core->addObject(teren);
    //core->addObject(boxik);
    //core->addObject(boxik2);
    core->addObject(house);
    //core->addObject(zombie);
    core->addObject(tree);
    core->start();
}
