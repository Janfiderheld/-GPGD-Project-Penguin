#ifndef BACKMAN_HEADER
#define BACKMAN_HEADER

#include <Level/BackgroundLayer.h>
#include <vector>
#include <Technicals/Texture.h>

class BackgroundManager {
private:
	const int LayerAmount = 2;

	std::vector<BackgroundLayer> _layers;

	void createLayers(glm::vec3 startPos);
	
public:
	BackgroundManager(glm::vec3 startPos);

	int getLayerAmount();
	Texture* getTextureForLayer(int layerNo);
	glm::vec3 getPositionForLayer(int layerNo);
};

#endif // BACKMAN_HEADER