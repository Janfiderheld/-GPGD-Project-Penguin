#include "Texture.h"

Texture::Texture(const char* fileLocation, GLint format)
{
	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	
	unsigned char* imageData = stbi_load(fileLocation, &_width, &_height, &_noColorChannels, 0);
	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture. Id: " << TextureId << std::endl;
	}
	stbi_image_free(imageData);
}

int Texture::getWidth()
{
	return _width;
}

int Texture::getHeight()
{
	return _height;
}

int Texture::getNumberOfColorChannels()
{
	return _noColorChannels;
}

void Texture::changeWrapping(GLint wrappingModeS, GLint wrappingModeT)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingModeS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingModeT);
}

void Texture::changeFiltering(GLint minFilterMode, GLint magFilterMode)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode);
}