#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <GLEW/glew.h>
#include <stb_image.h>
#include <iostream>

class Texture {
private:
	int _width;
	int _height;
	int _noColorChannels;

public:
	unsigned int TextureId;

	// Constructor to create the texture from a given file
	Texture(const char* fileLocation, GLint format);

	// Getter
	int getWidth();
	int getHeight();
	int getNumberOfColorChannels();

	// change parameters
	void changeWrapping(GLint wrappingModeS, GLint wrappingModeT);
	void changeFiltering(GLint minFilterMode, GLint magFilterMode);
};

#endif // TEXTURE_HEADER
