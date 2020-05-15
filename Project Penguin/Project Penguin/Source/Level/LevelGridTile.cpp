#include <Level/LevelGridTile.h>

LevelGridTile::LevelGridTile()
{
	// empty constructor
}

LevelGridTile::LevelGridTile(int x, int y, bool filled) {
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

}

bool LevelGridTile::isFilled() {
	return _filled;
}

void LevelGridTile::addToPit(int pitNo) {
	_pit = pitNo;
}

bool LevelGridTile::isGenerated() {
	return _generated;
}

float* LevelGridTile::getVertices()
{
	return _vertices;
}

glm::vec3 LevelGridTile::getPosition() {
	return glm::vec3(_x, _y, z);
}