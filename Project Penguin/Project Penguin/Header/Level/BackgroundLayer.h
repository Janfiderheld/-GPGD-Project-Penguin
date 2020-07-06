#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER

#include <GLM/glm.hpp>	
#include <Technicals/Texture.h>

class BackgroundLayer {
private:	
	Texture _background;
	glm::vec3 _position;
	int _layer;
	
public:
	BackgroundLayer();
	BackgroundLayer(glm::vec3 pos, Texture toUse, int layer);

	Texture getTexture();
	glm::vec3 getPosition();
};

#endif // BACKGROUND_HEADER