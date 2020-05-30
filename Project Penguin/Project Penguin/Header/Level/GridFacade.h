#ifndef GRID_FACADE
#define GRID_FACADE

#include <Level/LevelGrid.h>
#include <AABB.h>

class GridFacade {
private:
	LevelGrid* _grid;

public:
	GridFacade(LevelGrid* grid);

	bool checkForTwoTilesInX(int x, int y, AABB objHitbox);
	bool checkForTwoTilesInY(int x, int y, AABB objHitbox);
	bool checkForWall(int x, int y);
	bool checkForEndArea(int x, int y);
};

#endif // GRID_FACADE
