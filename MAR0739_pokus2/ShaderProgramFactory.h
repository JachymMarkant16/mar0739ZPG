#pragma once
#include "ShaderProgramType.h"
#include "ShaderProgram.h"
class ShaderProgramFactory
{
public:
	static ShaderProgram* createShaderProgram(ShaderProgramType type);
};

