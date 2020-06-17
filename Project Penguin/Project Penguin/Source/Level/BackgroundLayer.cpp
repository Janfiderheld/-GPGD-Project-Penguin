#include <Level/BackgroundLayer.h>

/// <summary>
/// Factor by which each layers speed differentiates
/// </summary>
float BackgroundLayer::LayerSpeedFactor = 0.8;

/// <summary>
/// Scale of the Texture
/// </summary>
glm::vec3 BackgroundLayer::Scale = glm::vec3(40.0, 20.0f, 1.0f);

/// <summary>
/// Empty default constructor
/// </summary>
BackgroundLayer::BackgroundLayer() :
	DrawableVertices(_position.x, _position.y, _position.x, _position.y) {
}

/// <summary>
/// Initializes this background layer by setting the position, the texture to draw and which layer it is.
/// </summary>
/// <param name="pos">starting position of this layer</param>
/// <param name="toUse">Texture for this layer</param>
/// <param name="layer">number of this layer (0 = nearest to camera)</param>
BackgroundLayer::BackgroundLayer(glm::vec2 pos, Texture toUse, int layer) : _background(toUse),
	DrawableVertices(pos.x, pos.y, pos.x + toUse.getWidth(), pos.y + toUse.getHeight()) {
	_position = glm::vec3(pos, _z);
	_layer = layer;
}

/// <summary>
/// Returns the Texture of this background layer
/// </summary>
Texture BackgroundLayer::getTexture() {
	return _background;
}

/// <summary>
/// Returns the position of this layer
/// </summary>
glm::vec3 BackgroundLayer::getPosition() {
	return _position;
}

/// <summary>
/// Upgrades the position based on the camera position
/// </summary>
/// <param name="camX">x position</param>
void BackgroundLayer::upgradePosition(float camX) {
	if(_layer == 0) {
		_position.x = camX * LayerSpeedFactor;
	} else {
		_position.x = camX * (LayerSpeedFactor / _layer);
	}	
}