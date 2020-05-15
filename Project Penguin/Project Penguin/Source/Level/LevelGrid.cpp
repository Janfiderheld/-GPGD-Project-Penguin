#include <Level/LevelGrid.h>

// Generates the level grid based on a set of rules.
// The level has the dimension defined in its header.
// First the Initialization is done the same way every time.
// After that the procedural generation is based on a set of rules and defines the outline of the level.
// Finally the inner sections are filled
LevelGrid::LevelGrid() {
	size_t size = LevelHeight * LevelWidth;
	_level.resize(size);

	initializeGrid();
	generateBorder();
	//fillGrid();
}

// The following steps are the same for every generated grid:
// - certain amount of bottom rows is completely filled
// - starting area is not filled
void LevelGrid::initializeGrid() {
	for (int y = 0; y < FilledBottomRows; y++) {
		for (int x = 0; x < LevelWidth; x++) {
			size_t current = y * LevelWidth + x;
			_level.at(current) = LevelGridTile(x, y, true);
		}
	}

	int y = FilledBottomRows;
	for (int x = 0; x < StartingAreaWidth; x++) {
		size_t current = y * LevelWidth + x;
		_level.at(current) = LevelGridTile(x, y, false);
	}
}

// Rule #: There should be between 1 and 3 bottomless pits
void LevelGrid::generateBorder() {
	int noOfPits = rand() % 3 + 1;
	int currentX = StartingAreaWidth, currentY = FilledBottomRows;
	bool fulfillment = false;
	int probStepUp = 40;

	srand(time(NULL));
	while (!fulfillment) {
		int rndm = rand() % 100;
		if (rndm < probStepUp && currentY < LevelHeight - 1) {
			currentY++;
		}

		size_t current = currentY * LevelWidth + currentX;
		_level.at(current) = LevelGridTile(currentX, currentY, true);
		if (currentX < LevelWidth - 1) {
			currentX++;
		}
		else {
			fulfillment = true;
		}		
	}
}

void LevelGrid::fillGrid() {
	for (int x = 0; x < LevelWidth; x++) {
		for (int y = 0; y < LevelHeight; y++) {
			size_t current = x + y * LevelWidth;
			if (!_level.at(current).isGenerated()) {
				bool left = false;
				bool right = false;
				bool up = false;
				bool down = false;

				if (y < LevelHeight - 1) {
					if (_level.at(current + LevelWidth).isFilled()) {
						up = true;
					}
				}
				else {
					up = true;
				}

				if (y > 0) {
					if (_level.at(current - LevelWidth).isFilled()) {
						down = true;
					}
				}
				else {
					down = true;
				}

				if (x < LevelWidth - 1) {
					if (_level.at(current + 1).isFilled()) {
						right = true;
					}
				}
				else {
					right = true;
				}

				if (x > 0) {
					if (_level.at(current - 1).isFilled()) {
						left = true;
					}
				}
				else {
					left = true;
				}
				_level.at(current) = LevelGridTile(x, y, up && down && left && right);
			}
		}
	}
}

void LevelGrid::drawGrid(Texture tex) {

}

LevelGridTile LevelGrid::getTileFromGrid(int x, int y)
{
	return _level.at(x + y * LevelWidth);
}

int LevelGrid::getWidth()
{
	return LevelWidth;
}

int LevelGrid::getHeight()
{
	return LevelHeight;
}
