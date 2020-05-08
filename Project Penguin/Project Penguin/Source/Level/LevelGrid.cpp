#include <Level/LevelGrid.h>

LevelGrid::LevelGrid(int width, int height, int tileSize) : _level{} {
	_actualWidth = width;
	_actualHeight = height;

	for (int i = 0; i < _actualWidth; i++) {
		for (int j = 0; j < _actualHeight; j++) {
			// TODO: Fill with procedural level generation
			_level[i][j] = LevelGridTile(i, j, tileSize);
		}
	}
}