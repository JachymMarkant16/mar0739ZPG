#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class ShaderProgram
{
private:
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
	void createAndCompileShaders(const char* vertexShaderFileName, const char* fragmentShaderFileName);
public:
	ShaderProgram();
	ShaderProgram(const char* vertexShader, const char* fragmentShader);
	GLuint getShaderProgram();
};

