#include <Level/BackgroundLayer.h>

/// <summary>
/// Empty default constructor
/// </summary>
BackgroundLayer::BackgroundLayer() {
}

/// <summary>
/// Initializes this background layer by setting the texture for ice and desert to draw and which layer it is
/// </summary>
/// <param name="ice">Texture before changing by the theme changing barrier</param>
/// <param name="desert">Texture after changing by the theme changing barrier</param>
/// <param name="layer">number of this layer (0 = nearest to camera)</param>
BackgroundLayer::BackgroundLayer(Texture ice, Texture desert, int layer) : _ice(ice), _desert(desert) {
	_layer = layer;
}

/// <summary>
/// Returns the ice Texture of this background layer
/// </summary>
Texture* BackgroundLayer::getIceTexture() {
	return &_ice;
}

/// <summary>
/// Returns the desert Texture of this background layer
/// </summary>
Texture* BackgroundLayer::getDesertTexture() {
	return &_desert;
}