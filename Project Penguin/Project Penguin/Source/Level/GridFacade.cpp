#include <Level/GridFacade.h>

GridFacade::GridFacade(LevelGrid* grid)
{
	_grid = grid;
}

bool GridFacade::checkForTwoTilesInX(int x, int y, AABB objHitbox) {
	if (x >= _grid->getWidth() || x < 0) {
		return false;
	}

	AABB left = _grid->getTileFromGrid(x, y).getHitbox();
	
	if (objHitbox.getMinX() >= left.getMinX() &&
		objHitbox.getMaxX() < left.getMaxX()) {
		return true;
	} else {
		return false;
	}	
}

bool GridFacade::checkForTwoTilesInY(int x, int y, AABB objHitbox) {
	if (y >= _grid->getHeight() || y < 0) {
		return false;
	}

	AABB bottom = _grid->getTileFromGrid(x, y).getHitbox();

	if (objHitbox.getMinY() >= bottom.getMinY() &&
		objHitbox.getMaxY() < bottom.getMaxY()) {
		return true;
	}
	else {
		return false;
	}
}

bool GridFacade::checkForWall(int x, int y) {
	if (x >= _grid->getWidth() ||
		x < 0 ||
		y >= _grid->getHeight() ||
		y <= 0) {
		return false;
	}

	return _grid->getTileFromGrid(x, y).isFilled();
}

bool GridFacade::checkForEndArea(int x, int y) {
	if (x >= _grid->getWidth() ||
		x < 0 ||
		y >= _grid->getHeight() ||
		y <= 0) {
		return false;
	}

	return _grid->getTileFromGrid(x, y).getLocation() == END_AREA;
}