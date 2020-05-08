#ifndef GRIDTILE_HEADER
#define GRIDTILE_HEADER

#include <Texture.h>

class LevelGridTile {
private:
	int _x, _y;
	float _size;

public:
	LevelGridTile();
	LevelGridTile(int x, int y, int size);
};

#endif // GRIDTILE_HEADER
