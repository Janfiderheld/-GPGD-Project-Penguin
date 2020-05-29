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

	//return _grid->getTileFromGrid(x, y - 1).isFilled();

	LevelGridTile bottom = _grid->getTileFromGrid(x, y - 1);
	if (bottom.isFilled()) {
		return objHitbox.checkCollision(bottom.getHitbox());
	} else {
		return false;
	}	
}

bool GridFacade::checkForCeiling(int x, int y, AABB objHitbox)
{
	if (y >= _grid->getHeight()) {
		return true;
	}

	return _grid->getTileFromGrid(x, y + 1).isFilled();

	/*LevelGridTile top = _grid->getTileFromGrid(x, y + 1);
	if (top.isFilled()) {
		return objHitbox.checkCollision(top.getHitbox());
	} else {		
		return false;
	}*/
}

bool GridFacade::checkForLeftWall(int x, int y, AABB objHitbox)
{
	if (x < 0) {
		return true;
	}

	//return _grid->getTileFromGrid(x - 1, y).isFilled();

	LevelGridTile left = _grid->getTileFromGrid(x - 1, y);
	if (left.isFilled()) {
		return objHitbox.checkCollision(left.getHitbox());
	} else {		
		return false;
	}
}

bool GridFacade::checkForRightWall(int x, int y, AABB objHitbox)
{
	if (x >= _grid->getWidth()) {
		return false;
	}

	return _grid->getTileFromGrid(x + 1, y).isFilled();

	/*LevelGridTile right = _grid->getTileFromGrid(x + 1, y);
	if (right.isFilled()) {
		return objHitbox.checkCollision(right.getHitbox());
	} else {		
		return false;
	}*/
}