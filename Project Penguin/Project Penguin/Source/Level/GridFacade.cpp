#include <Level/GridFacade.h>

GridFacade::GridFacade(LevelGrid* grid)
{
	_grid = grid;
}

bool GridFacade::checkForGround(int x, int y, AABB objHitbox)
{
	if (y <= 0) {
		return false;
	}

	LevelGridTile bottom = _grid->getTileFromGrid(x, y - 1);
	return objHitbox.checkCollision(bottom.getHitbox());
}

bool GridFacade::checkForLeftWall(int x, int y, AABB objHitbox)
{
	if (x <= 0) {
		return false;
	}

	LevelGridTile left = _grid->getTileFromGrid(x - 1, y);
	return objHitbox.checkCollision(left.getHitbox());
}

bool GridFacade::checkForRightWall(int x, int y, AABB objHitbox)
{
	if (x >= _grid->getWidth()) {
		return false;
	}

	LevelGridTile right = _grid->getTileFromGrid(x + 1, y);
	return objHitbox.checkCollision(right.getHitbox());
}