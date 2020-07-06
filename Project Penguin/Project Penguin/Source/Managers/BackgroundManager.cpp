#include <Managers/BackgroundManager.h>

/// <summary>
/// Creates the defined amount of layers and gives them the corresponding texture
/// </summary>
void BackgroundManager::createLayers() {
	for(int i = 0; i < LayerAmount; i++) {
		Texture iceLayerTex(("IceBackground" + std::to_string(i) + ".png").c_str(), GL_RGBA);
		Texture desertLayerTex(("DesertBackground" + std::to_string(i) + ".png").c_str(), GL_RGBA);
		_layers.at(i) = BackgroundLayer(iceLayerTex, desertLayerTex, i);
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
/// Returns the ice texture for a given layer
/// </summary>
/// <param name="layerNo">number of layer in [0, LayerAmount)</param>
Texture* BackgroundManager::getIceTextureForLayer(int layerNo) {
	if (layerNo < 0 || layerNo >= LayerAmount) {
		return nullptr;
	}

	return _layers.at(layerNo).getIceTexture();
}

/// <summary>
/// Returns the desert texture for a given layer
/// </summary>
/// <param name="layerNo">number of layer in [0, LayerAmount)</param>
Texture* BackgroundManager::getDesertTextureForLayer(int layerNo) {
	if (layerNo < 0 || layerNo >= LayerAmount) {
		return nullptr;
	}

	return _layers.at(layerNo).getDesertTexture();
}