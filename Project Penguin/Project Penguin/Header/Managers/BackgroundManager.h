#ifndef BACKMAN_HEADER
#define BACKMAN_HEADER

#include <Level/BackgroundLayer.h>
#include <vector>
#include <Technicals/Texture.h>

class BackgroundManager {
private:
	const int LayerAmount = 1;

	std::vector<BackgroundLayer> _layers;

	void createLayers();
	
public:
	BackgroundManager();

	int getLayerAmount();
	float getOffsetForLayer(int layerNo);
	Texture* getTextureForLayer(int layerNo);
	float* getVerticesForLayer(int layerNo);
};

#endif // BACKMAN_HEADER