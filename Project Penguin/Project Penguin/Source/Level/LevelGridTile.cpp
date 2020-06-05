#include <Level/LevelGridTile.h>

/// <summary>
/// Creates the bounding box & the vertices based on the tiles position 
/// </summary>
LevelGridTile::LevelGridTile() : DrawableVertices(_x, _y, _x + Size, _y + Size), _hitbox(getPosition(), Size) {
	// empty constructor
}

/// <summary>
/// Creates the bounding box & the vertices based on the tiles position, 
/// changes the filling to empty and sets the x and y values
/// </summary>
/// <param name="x">position on the x-axis</param>
/// <param name="y">position on the y-axis</param>
LevelGridTile::LevelGridTile(int x, int y) : DrawableVertices(x, y, x + Size, y + Size), _hitbox(getPosition(), Size) {
	_x = x;
	_y = y;
	_generated = true;
	changeFilling(false);
	_hitbox = AABB(getPosition(), Size);
}

/// <summary>
/// Returns true if the tile is filled (= has a texture)
/// </summary>
bool LevelGridTile::isFilled() {
	return _filled;
}

/// <summary>
/// Changes if the tile is filled based on the given value
/// </summary>
void LevelGridTile::changeFilling(bool status) {
	_filled = status;
}

/// <summary>
/// Returns true if the tile was generated
/// </summary>
bool LevelGridTile::isGenerated() {
	return _generated;
}

/// <summary>
/// Changes the location of the tile to the given value 
/// => if it belongs to the starting or end area or not
/// </summary>
void LevelGridTile::changeLocation(TileLocation newLoc) {
	_loc = newLoc;
}

/// <summary>
/// Returns the location of this tile
/// </summary>
TileLocation LevelGridTile::getLocation() {
	return _loc;
}

/// <summary>
/// Sets bool indicating if this tile has an outline border to the left
/// </summary>
void LevelGridTile::setLeftBorder(bool left) {
	_left = left;
}

/// <summary>
/// Sets bool indicating if this tile has an outline border to the top
/// </summary>
void LevelGridTile::setTopBorder(bool top) {
	_top = top;
}

/// <summary>
/// Sets bool indicating if this tile has an outline border to the right
/// </summary>
void LevelGridTile::setRightBorder(bool right) {
	_right = right;
}

/// <summary>
/// Sets bool indicating if this tile has an outline border to the ground
/// </summary>
void LevelGridTile::setBottomBorder(bool bottom) {
	_bottom = bottom;
}

/// <summary>
/// Returns which borders this tile has coded in a byte: xxxx3210
/// last Bit (0) = bottom border
/// seventh bit (1) = top border
/// sixth bit (2) = right border
/// fifth bit (3) = left border
/// </summary>
unsigned char LevelGridTile::getBorderForTexture() {
	unsigned char toReturn = 0;

	if (_left) {
		toReturn |= 0x08;
	}
	if (_right) {
		toReturn |= 0x04;
	}
	if (_top) {
		toReturn |= 0x02;
	}
	if (_bottom) {
		toReturn |= 0x01;
	}

	return toReturn;
}

/// <summary>
/// Returns the position of this tile
/// </summary>
glm::vec3 LevelGridTile::getPosition() {
	return glm::vec3(_x, _y, _z);
}

/// <summary>
///  Returns the bounding box of this tile
/// </summary>
AABB LevelGridTile::getHitbox() {
	return _hitbox;
}