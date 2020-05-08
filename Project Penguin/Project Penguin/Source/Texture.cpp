#include "Texture.h"

// Constructor which loads a file in the fiven format 
Texture::Texture(const char* fileName, GLint format)
{
	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	
	unsigned char* imageData = stbi_load(_location.append(fileName).c_str(), &_width, &_height, &_noColorChannels, 0);
	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture. Id: " << TextureId << std::endl;
	}
	stbi_image_free(imageData);
}

// returns the width of the texture
int Texture::getWidth()
{
	return _width;
}

// returns the height of the texture
int Texture::getHeight()
{
	return _height;
}

// returns the number of color channels in the texture
int Texture::getNumberOfColorChannels()
{
	return _noColorChannels;
}

// changes the Texture Wrapping in s and t direction to the given value
void Texture::changeWrapping(GLint wrappingMode)
{
	changeWrapping(wrappingMode, wrappingMode);
}

// changes the Texture Wrapping in s and t direction to the given values
void Texture::changeWrapping(GLint wrappingModeS, GLint wrappingModeT)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingModeS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingModeT);
}

// changes the Texture Filtering modes to the given value
void Texture::changeFiltering(GLint filterMode)
{
	changeFiltering(filterMode, filterMode);
}

// changes the Texture Filtering modes to the given values
void Texture::changeFiltering(GLint minFilterMode, GLint magFilterMode)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode);
}