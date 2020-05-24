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
	if (!bottom.isFilled()) {
		return false;
	} else {
		return objHitbox.checkCollision(bottom.getHitbox());
	}	
}

bool GridFacade::checkForCeiling(int x, int y, AABB objHitbox)
{
	if (y >= _grid->getHeight()) {
		return true;
	}

	LevelGridTile top = _grid->getTileFromGrid(x, y + 1);
	if (!top.isFilled()) {
		return false;
	}
	else {
		return objHitbox.checkCollision(top.getHitbox());
	}
}

bool GridFacade::checkForLeftWall(int x, int y, AABB objHitbox)
{
	if (x < 0) {
		return true;
	}

	LevelGridTile left = _grid->getTileFromGrid(x - 1, y);
	if (!left.isFilled()) {
		return false;
	} else {
		return objHitbox.checkCollision(left.getHitbox());
	}
}

bool GridFacade::checkForRightWall(int x, int y, AABB objHitbox)
{
	if (x >= _grid->getWidth()) {
		return false;
	}

	LevelGridTile right = _grid->getTileFromGrid(x + 1, y);
	if (!right.isFilled()) {
		return false;
	} else {
		return objHitbox.checkCollision(right.getHitbox());
	}
}