#ifndef GRID_FACADE
#define GRID_FACADE

#include <Level/LevelGrid.h>
#include <Technicals/AABB.h>
#include <GLM/glm.hpp>
#include <vector>

class GridFacade {
private:
	LevelGrid* _grid;

public:
	GridFacade(LevelGrid* grid);

	bool checkForTwoTilesInX(int x, int y, AABB objHitbox);
	bool checkForTwoTilesInY(int x, int y, AABB objHitbox);
	bool checkForWall(int x, int y);
	bool checkForEndArea(int x, int y);

	std::vector<glm::vec2>* getCollectablePositions();
	int generateRandomForPlacement();
	int getHeightForXPos(int x);
};

#endif // GRID_FACADE
