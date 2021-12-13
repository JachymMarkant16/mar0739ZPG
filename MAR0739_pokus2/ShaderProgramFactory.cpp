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
	case ShaderProgramType::ThreeD:
		return new ShaderProgram("3dVertex.txt", "3dFragment.txt");
		break;
	case ShaderProgramType::ThreeDPhong:
		return new ShaderProgram("3dPhongVertex.txt", "3dPhongFragment.txt");
		break;
	}
}