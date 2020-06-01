#include "Texture.h"

/// <summary>
/// Loads an image from the given file in the given format and saves it as a texture.
/// Also sets wrapping and filtering to default values (Repeat & linear filtering).
/// </summary>
/// <param name="fileName">name of the image file</param>
/// <param name="format">format of the image file (ex. RGBA)</param>
Texture::Texture(const char* fileName, GLint format) {
	glGenTextures(1, &TextureId);
	glBindTexture(GL_TEXTURE_2D, TextureId);
	
	stbi_set_flip_vertically_on_load(true);
	unsigned char* imageData = stbi_load(_location.append(fileName).c_str(), &_width, &_height, &_noColorChannels, 0);
	if (imageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "Failed to load texture. Id: " << TextureId << std::endl;
	}
	stbi_image_free(imageData);

	changeWrapping(GL_REPEAT);
	changeFiltering(GL_LINEAR);
}

/// <summary>
/// Returns the width of the texture
/// </summary>
int Texture::getWidth() {
	return _width;
}

/// <summary>
/// Returns the height of the texture
/// </summary>
int Texture::getHeight() {
	return _height;
}

/// <summary>
/// Returns the number of color channels on this texture
/// </summary>
int Texture::getNumberOfColorChannels() {
	return _noColorChannels;
}

/// <summary>
/// Changes which wrapping mode is used in both directions based on the given parameter
/// </summary>
/// <param name="wrappingMode">new wrapping mode to use</param>
void Texture::changeWrapping(GLint wrappingMode) {
	changeWrapping(wrappingMode, wrappingMode);
}

/// <summary>
/// Changes the wrapping mode for both directions independently
/// </summary>
/// <param name="wrappingModeS">new wrapping mode for the s-axis</param>
/// <param name="wrappingModeT">new wrapping mode for the t-axis</param>
void Texture::changeWrapping(GLint wrappingModeS, GLint wrappingModeT) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingModeS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingModeT);
}

/// <summary>
/// Changes which filtering method is used in both directions based on the given parameter
/// </summary>
/// <param name="filterMode">new filter method to use</param>
void Texture::changeFiltering(GLint filterMode) {
	changeFiltering(filterMode, filterMode);
}

/// <summary>
/// Changes the filtering method for both directions independently
/// </summary>
/// <param name="minFilterMode">new filter method for minification</param>
/// <param name="magFilterMode">new filter method for magnification</param>
void Texture::changeFiltering(GLint minFilterMode, GLint magFilterMode) {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode);
}