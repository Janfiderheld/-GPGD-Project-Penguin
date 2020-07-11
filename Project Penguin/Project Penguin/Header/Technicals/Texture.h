#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

#include <GL/glew.h>
#include <Technicals/stb_image.h>
#include <iostream>
#include <string>

class Texture {
private:
	int _width;
	int _height;
	int _noColorChannels;

	std::string _locDebug = "../Assets/Textures/";
	std::string _locRelease = "./Assets/Textures/";

public:
	unsigned int TextureId;

	Texture();
	Texture(const char* fileName, GLint format);

	int getWidth();
	int getHeight();
	int getNumberOfColorChannels();

	void changeWrapping(GLint wrappingMode);
	void changeWrapping(GLint wrappingModeS, GLint wrappingModeT);
	void changeFiltering(GLint filterMode);
	void changeFiltering(GLint minFilterMode, GLint magFilterMode);
};

#endif // TEXTURE_HEADER