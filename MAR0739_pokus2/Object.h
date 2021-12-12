#pragma once
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

#include "ShaderProgram.h"
#include <iostream>
#include "ShaderProgram.h"
#include "ShaderProgramFactory.h"
#include "ShaderProgramType.h"
class Object
{
public:
	struct Vertex
	{
		float Position[3];
		float Normal[3];
		float Texture[2];
		float Tangent[3];
	};
	virtual void DrawObject(glm::mat4 view, glm::mat4 projection) = 0;
	void MoveRight(int size);
	void Scale(int size);
protected:
    void InitVars(ShaderProgramType shaderProgram, glm::mat4 defaultMat = glm::mat4(1.0f));
    void InitVAO();
    void InitVBO(float* points, int sizeOfPoints);
	void InitVBO(Vertex* points, int sizeOfPoints);
    void SetVertexAttribs(ShaderProgramType shaderProgram);
    GLuint VAO = 0;
    GLuint VBO = 0;
    int sizeOfPoints;
	ShaderProgram* shaderProgram;
	glm::mat4 modelMatrix;
};

