#ifndef GRID_FACADE
#define GRID_FACADE

#include <Level/LevelGrid.h>
#include <AABB.h>

class GridFacade {
private:
	LevelGrid* _grid;

public:
	GridFacade(LevelGrid* grid);

	bool checkForGround(int x, int y, AABB objHitbox);
	bool checkForCeiling(int x, int y, AABB objHitbox);
	bool checkForLeftWall(int x, int y, AABB objHitbox);
	bool checkForRightWall(int x, int y, AABB objHitbox);
};

#endif // GRID_FACADE
