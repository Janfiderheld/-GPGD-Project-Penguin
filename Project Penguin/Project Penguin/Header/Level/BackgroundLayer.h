#ifndef BACKGROUND_HEADER
#define BACKGROUND_HEADER

#include <GLM/glm.hpp>	
#include <Technicals/Texture.h>

class BackgroundLayer {
private:	
	Texture _ice;
	Texture _desert;
	int _layer;
	
public:
	BackgroundLayer();
	BackgroundLayer(Texture ice, Texture desert, int layer);

	Texture* getIceTexture();
	Texture* getDesertTexture();
};

#endif // BACKGROUND_HEADER