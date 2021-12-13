#include "TextureController.h"
void TextureController::loadNewTexture(ShaderProgramType shaderType, std::string name, std::string path) {
    GLuint textureId;
	switch (shaderType) {
	case ShaderProgramType::SkyBox:
        glActiveTexture(availableTexture);
        textureId = SOIL_load_OGL_cubemap(
            "..\\..\\Textures\\posx.jpg",
            "..\\..\\Textures\\negx.jpg",
            "..\\..\\Textures\\posy.jpg",
            "..\\..\\Textures\\negy.jpg",
            "..\\..\\Textures\\posz.jpg",
            "..\\..\\Textures\\negz.jpg",
            SOIL_LOAD_RGB,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS
        );

        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
		break;
	case ShaderProgramType::TwoD:
    case ShaderProgramType::ThreeDPhong:
    case ShaderProgramType::ThreeD:
		glActiveTexture(availableTexture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		textureId = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureId == NULL) {
            std::cout << "An error occurred while loading image." << std::endl;
            exit(EXIT_FAILURE);
        }
        glBindTexture(GL_TEXTURE_2D, textureId);
		break;
	}
    this->loadedTextures.insert(std::pair<std::string, int>(name, textureCount));
	availableTexture++;
    textureCount++;
}
int TextureController::getTextureByName(std::string name) {
    return this->loadedTextures[name.c_str()];
}
TextureController::TextureController() {
}