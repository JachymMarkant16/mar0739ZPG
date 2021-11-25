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

int main()
{
    Core* core = core->getInstance();
    core->setData(800, 600, "ZPG");
    core->initCore();
    //create and compile shaders
    ShaderProgram shaderProgram("2dVertex.txt", "2dFragment.txt");
    ModelObject triangle(box, sizeof(box), shaderProgram);
    core->addObject(triangle);
    core->start();
}