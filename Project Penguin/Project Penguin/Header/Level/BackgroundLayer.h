#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER

#include <Technicals/Texture.h>
#include <Technicals/DrawableVertices.h>
#include <GLM/glm.hpp>	

class BackgroundLayer : public DrawableVertices {
private:
	static float LayerSpeedFactor;
	
	Texture _background;
	glm::vec3 _position;
	int _layer;
	
public:
	static glm::vec3 Scale;

	BackgroundLayer();
	BackgroundLayer(glm::vec2 pos, Texture toUse, int layer);

	Texture getTexture();
	glm::vec3 getPosition();
	
	void upgradePosition(float camX);
};

#endif // BACKGROUND_HEADER