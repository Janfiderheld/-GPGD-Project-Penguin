#include <Level/LevelGridTile.h>

LevelGridTile::LevelGridTile() : _hitbox(getPosition(), 1) {
	// empty constructor
}

LevelGridTile::LevelGridTile(int x, int y, bool filled) : _hitbox(getPosition(), 1) {
	_x = x;
	_y = y;
	_filled = filled;
	_generated = true;

	// TODO: Find a possiblity to use a loop
	_vertices[0] = (float)(_x + 1);
	_vertices[1] = (float)(_y + 1);
	_vertices[2] = z;
	_vertices[3] = 1.0f;
	_vertices[4] = 1.0f;
	_vertices[5] = (float)(_x + 1);
	_vertices[6] = (float)_y;
	_vertices[7] = z;
	_vertices[8] = 1.0f;
	_vertices[9] = 0.0f;
	_vertices[10] = (float)_x;
	_vertices[11] = (float)_y;
	_vertices[12] = z;
	_vertices[13] = 0.0f;
	_vertices[14] = 0.0f;
	_vertices[15] = (float)_x;
	_vertices[16] = (float)(_y + 1);
	_vertices[17] = z;
	_vertices[18] = 0.0f;
	_vertices[19] = 1.0f;

	_hitbox = AABB(getPosition(), 1);
}

bool LevelGridTile::isFilled() {
	return _filled;
}

bool LevelGridTile::isGenerated() {
	return _generated;
}

void LevelGridTile::changeLocation(Location newLoc) {
	_loc = newLoc;
}

Location LevelGridTile::getLocation() {
	return _loc;
}

void LevelGridTile::setLeftBorder(bool left) {
	_left = left;
}

void LevelGridTile::setTopBorder(bool top) {
	_top = top;
}

void LevelGridTile::setRightBorder(bool right) {
	_right = right;
}

void LevelGridTile::setBottomBorder(bool bottom) {
	_bottom = bottom;
}

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

float* LevelGridTile::getVertices()
{
	return _vertices;
}

glm::vec3 LevelGridTile::getPosition() {
	return glm::vec3(_x, _y, z);
}

AABB LevelGridTile::getHitbox() {
	return _hitbox;
}