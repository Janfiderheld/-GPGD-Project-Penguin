#ifndef BACKMAN_HEADER
#define BACKMAN_HEADER

#include <Level/BackgroundLayer.h>
#include <vector>
#include <Technicals/Texture.h>

class BackgroundManager {
private:
	const int LayerAmount = 2;

	std::vector<BackgroundLayer> _layers;

	void createLayers();
	
public:
	BackgroundManager();

	int getLayerAmount();
	Texture* getIceTextureForLayer(int layerNo);
	Texture* getDesertTextureForLayer(int layerNo);
};

#endif // BACKMAN_HEADER