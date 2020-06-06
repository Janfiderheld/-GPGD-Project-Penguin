#include <Managers/GridFacade.h>

/// <summary>
/// Constructor. Gets the pointer to the level for which this works as a facade.
/// </summary>
/// <param name="grid">level grid to manage the access to</param>
GridFacade::GridFacade(LevelGrid* grid) {
	_grid = grid;
}

/// <summary>
/// Checks for the given hitbox if it overlaps with only one or two tiles on the x-axis.
/// </summary>
/// <param name="x">Position to check for in x-axis</param>
/// <param name="y">Position to check for on y-axis</param>
/// <param name="objHitbox">hitbox to check with</param>
/// <returns>true if the hitbox overlaps wih two tiles</returns>
bool GridFacade::checkForTwoTilesInX(int x, int y, AABB objHitbox) {
	if (x >= _grid->getWidth() || x < 0 ||
		y >= _grid->getHeight() || y <= 0) {
		return false;
	}

	AABB left = _grid->getTileFromGrid(x, y).getHitbox();
	
	if (objHitbox.getMinX() >= left.getMinX() &&
		objHitbox.getMaxX() <= left.getMaxX()) {
		return true;
	} else {
		return false;
	}	
}

/// <summary>
/// Checks for the given hitbox if it overlaps with only one or two tiles on the y-axis.
/// </summary>
/// <param name="x">Position to check for in x-axis</param>
/// <param name="y">Position to check for on y-axis</param>
/// <param name="objHitbox">hitbox to check with</param>
/// <returns>true if the hitbox overlaps wih two tiles</returns>
bool GridFacade::checkForTwoTilesInY(int x, int y, AABB objHitbox) {
	if (x >= _grid->getWidth() || x < 0 ||
		y >= _grid->getHeight() || y <= 0) {
		return false;
	}

	AABB bottom = _grid->getTileFromGrid(x, y).getHitbox();

	if (objHitbox.getMinY() >= bottom.getMinY() &&
		objHitbox.getMaxY() <= bottom.getMaxY()) {
		return true;
	} else {
		return false;
	}
}

/// <summary>
/// Checks if the tile at the given position is a wall (= filled) or not.
/// </summary>
/// <param name="x">Position to check for in x-axis</param>
/// <param name="y">Position to check for on y-axis</param>
/// <returns>true if the tile is filled.</returns>
bool GridFacade::checkForWall(int x, int y) {
	if (x >= _grid->getWidth() || x < 0 ||
		y >= _grid->getHeight() || y <= 0) {
		return false;
	}

	return _grid->getTileFromGrid(x, y).isFilled();
}

/// <summary>
/// Checks if the tile at the given position is part of the end area.
/// </summary>
/// <param name="x">Position to check for in x-axis</param>
/// <param name="y">Position to check for on y-axis</param>
/// <returns>true if it is part of the end area</returns>
bool GridFacade::checkForEndArea(int x, int y) {
	if (x >= _grid->getWidth() || x < 0 ||
		y >= _grid->getHeight() || y <= 0) {
		return false;
	}

	return _grid->getTileFromGrid(x, y).getLocation() == END_AREA;
}

/// <summary>
/// Returns a reference to the vector containing the collectable positions on top of the platforms
/// </summary>
std::vector<glm::vec2>* GridFacade::getCollectablePositions() {
	return _grid->getCollectablePositions();
}

/// <summary>
/// Generates a random number in the area where platforms, pits & collectables can be placed
/// </summary>
int GridFacade::generateRandomForPlacement() {
	return _grid->generateRandomForPlacement();
}

/// <summary>
/// Returns the height of the level at the given x position.
/// </summary>
/// <param name="x">position to find the height for</param>
/// <returns>the height or 0 when this column is part of a pit</returns>
int GridFacade::getHeightForXPos(int x) {
	int y = 0;
	while (_grid->getTileFromGrid(x, y).isFilled()) {
		y++;
	}
	return y;
}