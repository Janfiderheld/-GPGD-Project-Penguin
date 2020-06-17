#ifndef BACKMAN_HEADER
#define BACKMAN_HEADER

#include <Level/BackgroundLayer.h>
#include <vector>
#include <Technicals/Texture.h>

class BackgroundManager {
private:
	const int LayerAmount = 2;

	std::vector<BackgroundLayer> _layers;

	void createLayers(glm::vec2 startPos);
	
public:
	BackgroundManager(glm::vec2 startPos);

	int getLayerAmount();
	Texture* getTextureForLayer(int layerNo);
	float* getVerticesForLayer(int layerNo);
	glm::vec3 getPositionForLayer(int layerNo);
	glm::vec3 getScaleForLayer(int layerNo);

	void updateLayers(float camX);
};

#endif // BACKMAN_HEADER