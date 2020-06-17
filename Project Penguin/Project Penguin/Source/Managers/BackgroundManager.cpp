#include <Managers/BackgroundManager.h>

/// <summary>
/// Creates the defined amount of layers and gives them the corresponding texture
/// </summary>
void BackgroundManager::createLayers(glm::vec2 startPos) {
	for(int i = 0; i < LayerAmount; i++) {
		Texture layerTex(("BackgroundLayer" + std::to_string(i) + ".png").c_str(), GL_RGBA);
		startPos.y += 2;
		_layers.at(i) = BackgroundLayer(startPos, layerTex, i);
	}
}

/// <summary>
/// Creates the layers and sets the dimension for the vector
/// </summary>
BackgroundManager::BackgroundManager(glm::vec2 startPos) {
	_layers.resize(LayerAmount);
	createLayers(startPos);
}

/// <summary>
/// Returns the amount of layers currently used
/// </summary>
int BackgroundManager::getLayerAmount() {
	return LayerAmount;
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

/// <summary>
/// Returns the position for a given layer to draw that layer
/// </summary>
/// <param name="layerNo">number of layer in [0, LayerAmount)</param>
glm::vec3 BackgroundManager::getPositionForLayer(int layerNo) {
	if (layerNo < 0 || layerNo >= LayerAmount) {
		return glm::vec3(0.0f);
	}

	return _layers.at(layerNo).getPosition();
}

/// <summary>
/// Returns the scale for a given layer
/// </summary>
/// <param name="layerNo">number of layer in [0, LayerAmount)</param>
glm::vec3 BackgroundManager::getScaleForLayer(int layerNo) {
	if (layerNo < 0 || layerNo >= LayerAmount) {
		return glm::vec3(0.0f);
	}

	return _layers.at(layerNo).Scale;
}

/// <summary>
/// Updates the position of the different layers
/// </summary>
/// <param name="camX">camera position as basis for the position update</param>
void BackgroundManager::updateLayers(float camX) {
	for(int i = 0; i < LayerAmount; i++)	{
		_layers.at(i).upgradePosition(camX);
	}
}