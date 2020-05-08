#include <Level/LevelGridTile.h>

LevelGridTile::LevelGridTile()
{
	// empty default constructor
}

LevelGridTile::LevelGridTile(int x, int y, int size) {
	_x = x;
	_y = y;

	_size = size;
}