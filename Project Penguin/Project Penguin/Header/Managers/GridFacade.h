#ifndef GRID_FACADE
#define GRID_FACADE

#include <Level/LevelGrid.h>
#include <Technicals/AABB.h>
#include <GLM/glm.hpp>
#include <vector>

class GridFacade {
private:
	const float OverlapFactor = 1.25f;
	const float RoundUpDiff = 0.05f;

	LevelGrid* _grid;

public:
	GridFacade(LevelGrid* grid);

	bool checkForTwoTiles(float minVal, float size);
	bool checkForWall(int x, int y);
	bool checkForEndArea(int x, int y);

	std::vector<glm::vec2>* getCollectablePositions();
	int generateRandomForPlacement();
	int getHeightForXPos(int x);
};

#endif // GRID_FACADE
