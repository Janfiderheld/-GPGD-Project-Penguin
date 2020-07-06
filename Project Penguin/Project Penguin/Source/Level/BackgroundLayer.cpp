#include <Level/BackgroundLayer.h>

/// <summary>
/// Empty default constructor
/// </summary>
BackgroundLayer::BackgroundLayer() {
}

/// <summary>
/// Initializes this background layer by setting the position, the texture to draw and which layer it is.
/// </summary>
/// <param name="pos">starting position of this layer</param>
/// <param name="toUse">Texture for this layer</param>
/// <param name="layer">number of this layer (0 = nearest to camera)</param>
BackgroundLayer::BackgroundLayer(glm::vec3 pos, Texture toUse, int layer) : _background(toUse) {
	_position = pos;
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