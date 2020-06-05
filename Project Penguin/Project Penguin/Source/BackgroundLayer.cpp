#include <BackgroundLayer.h>

/// <summary>
/// Factor by which each layers speed differentiates
/// </summary>
float BackgroundLayer::LayerSpeedFactor = 0.5;

/// <summary>
/// Empty default constructor
/// </summary>
/// <returns></returns>
BackgroundLayer::BackgroundLayer(): DrawableVertices(_position.x, _position.y, _position.x, _position.y) {
}

/// <summary>
/// Initializes this background layer by setting the position, the texture to draw and which layer it is.
/// </summary>
/// <param name="pos">starting position of this layer</param>
/// <param name="toUse">Texture for this layer</param>
/// <param name="layer">number of this layer (0 = nearest to camera)</param>
BackgroundLayer::BackgroundLayer(glm::vec2 pos, Texture toUse, int layer) : _background(toUse),
	DrawableVertices(pos.x, pos.y, pos.x + toUse.getWidth(), pos.y + toUse.getHeight()) {
	_z -= layer + 1;
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
/// Calculates & returns the horizontal offset which is used when reading from the texture.
/// </summary>
float BackgroundLayer::getOffset() {
	return _layer * LayerSpeedFactor;
}