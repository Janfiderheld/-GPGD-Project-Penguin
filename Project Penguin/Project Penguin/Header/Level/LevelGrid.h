#ifndef GRID_HEADER
#define GRID_HEADER

#include <Level/LevelGridTile.h>

class LevelGrid {
private:
	static const int MaxLevelWidth = 20;
	static const int MaxLevelHeight = 5;

	// TODO: Refine values when movement is implemented
	const float _friction = 2.0f;
	const float _gravity = 2.0f;

	LevelGridTile _level[MaxLevelWidth][MaxLevelHeight];
	int _actualWidth;
	int _actualHeight;

public:
	LevelGrid(int width, int height, int tileSize);
};

#endif // GRID_HEADER
