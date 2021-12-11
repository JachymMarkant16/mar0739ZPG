#include "ShaderProgramFactory.h"
ShaderProgram* ShaderProgramFactory::createShaderProgram(ShaderProgramType type) {
	switch (type) {
	case ShaderProgramType::Basic:
		return new ShaderProgram("basicVertex.txt", "basicFragment.txt");
		break;

	case ShaderProgramType::Color:
		return new ShaderProgram("colorVertex.txt", "colorFragment.txt");
		break;

	case ShaderProgramType::TwoD:
		return new ShaderProgram("2dVertex.txt", "2dFragment.txt");
		break;
	case ShaderProgramType::SkyBox:
		return new ShaderProgram("skyboxVertex.txt", "skyboxFragment.txt");
		break;
	}
}