#include <BackgroundManager.h>

/// <summary>
/// Creates the defined amount of layers and gives them the corresponding texture
/// </summary>
void BackgroundManager::createLayers() {
	for(int i = 0; i < LayerAmount; i++) {
		Texture layerTex(("BackgroundLayer" + std::to_string(i) + ".png").c_str(), GL_RGBA);
		_layers.at(i) = BackgroundLayer(glm::vec2(0.0f), layerTex, i);
	}
}

/// <summary>
/// Creates the layers and sets the dimension for the vector
/// </summary>
BackgroundManager::BackgroundManager() {
	_layers.resize(LayerAmount);
	createLayers();
}

/// <summary>
/// Returns the amount of layers currently used
/// </summary>
int BackgroundManager::getLayerAmount() {
	return LayerAmount;
}

/// <summary>
/// Returns the Offset for accessing the texture for a given layer
/// </summary>
/// <param name="layerNo">number of layer in [0, LayerAmount)</param>
float BackgroundManager::getOffsetForLayer(int layerNo) {
	if(layerNo < 0 || layerNo >= LayerAmount) { 
		return 0.0f;
	}

	return _layers.at(layerNo).getOffset();
}

/// <summary>
/// Returns the texture for a given layer
/// </summary>
/// <param name="layerNo">number of layer in [0, LayerAmount)</param>
Texture* BackgroundManager::getTextureForLayer(int layerNo) {
	if (layerNo < 0 || layerNo >= LayerAmount) {
		return nullptr;
	}

	return &(_layers.at(layerNo).getTexture());
}

/// <summary>
/// Returns the vertices for a given layer to draw that layer
/// </summary>
/// <param name="layerNo">number of layer in [0, LayerAmount)</param>
float* BackgroundManager::getVerticesForLayer(int layerNo) {
	if (layerNo < 0 || layerNo >= LayerAmount) {
		return nullptr;
	}

	return _layers.at(layerNo).getVertices();
}