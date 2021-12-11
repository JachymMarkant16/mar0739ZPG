#include "Texture2D.h"
int Texture2D::get_texture_unit_ID()
{
    return this->textureUnitID;
}

void Texture2D::unbind_texture()
{
    glActiveTexture(-1);
}
Texture2D::Texture2D()
{
	this->textureID = 0;
	this->textureUnitID = 0;
}

bool Texture2D::load_texture(const char* filename)
{
	glGenTextures(1, &textureID);
	textureUnitID = textureID;
	glActiveTexture(textureUnitID); // activate the texture unit first before binding texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	textureID = SOIL_load_OGL_texture(static_cast<const char*>(filename), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (textureID == -1)
	{
		fprintf(stderr, "Failed to load texture %s\n", filename);
		exit(-1);
		return false;
	}
	glActiveTexture(-1);

	return true;
}

void Texture2D::bind_texture()
{
	glActiveTexture(textureUnitID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);
	
}
