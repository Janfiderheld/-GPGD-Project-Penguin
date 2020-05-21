#include <Level/LevelGrid.h>

// Generates the level grid based on a set of rules.
// The level has the dimension defined in its header.
// First the Initialization is done the same way every time.
// After that the procedural generation is based on a set of rules and defines the outline of the level.
// Finally the inner sections are filled
LevelGrid::LevelGrid() {
	srand(time(NULL));

	size_t size = LevelHeight * LevelWidth;
	_level.resize(size);	

	initializeGrid();
	generateBottom();
	addPlattforms();
	addPits();

	setTileBorders();
}

// The following steps are the same for every generated grid:
// - certain amount of bottom rows is completely filled
// - starting area is not filled
void LevelGrid::initializeGrid() {
	for (int y = 0; y <= FilledBottomRows; y++) {
		for (int x = 0; x <= StartingAreaWidth; x++) {
			size_t current = y * LevelWidth + x;
			_level.at(current) = LevelGridTile(x, y, y != FilledBottomRows);
			if (y == FilledBottomRows - 1 && x != StartingAreaWidth) {
				_level.at(current).changeLocation(START_AREA);
			}			
		}
	}

	for (int y = 0; y <= FilledBottomRows; y++) {
		for (int x = LevelWidth - EndAreaWidth; x < LevelWidth; x++) {
			size_t current = y * LevelWidth + x;
			_level.at(current) = LevelGridTile(x, y, y != FilledBottomRows);
			if (y == FilledBottomRows - 1) {
				_level.at(current).changeLocation(END_AREA);
			}
		}
	}
}

void LevelGrid::generateBottom() {
	int currentX = StartingAreaWidth;
	int currentY = FilledBottomRows - 1;
	int countPlain = PlainWidth;
	bool levelEndReached = false;

	while (!levelEndReached) {
		int rndm = rand() % 100;
		switch (state) {
		case START:
			if (rndm < SameGoUp && currentY < MaxBottomHeight) {
				currentY++;
				state = HIGH;
			}
			else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					fillTilesBelow(currentX, currentY);
				}
				else {
					levelEndReached = true;
				}
			}
			break;

		case HIGH:
			if (countPlain <= 0) {
				countPlain = PlainWidth;
				state = HIGH_FIN;
			}
			if (currentX < LevelWidth - EndAreaWidth - 1) {
				currentX++;
				countPlain--;
				fillTilesBelow(currentX, currentY);
			}
			else {
				levelEndReached = true;
			}			
			break;

		case HIGH_FIN:
			if (rndm < HighGoUp) {
				if (currentY < MaxBottomHeight) {
					currentY++;
					state = HIGH;
				} else {
					continue;
				}
			}
			else if (rndm >= HighGoUp && rndm < HighGoUp + HighGoDown) {
				if (currentY >= FilledBottomRows) {
					currentY--;
					state = LOW;
				}
				else {
					continue;
				}				
			}
			else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					fillTilesBelow(currentX, currentY);
				}
				else {
					levelEndReached = true;
				}
			}
			break;

		case LOW:
			if (countPlain <= 0) {
				countPlain = PlainWidth;
				state = HIGH_FIN;
			}
			if (currentX < LevelWidth - EndAreaWidth - 1) {
				currentX++;
				countPlain--;
				fillTilesBelow(currentX, currentY);
			}
			else {
				levelEndReached = true;
			}
			break;

		case LOW_FIN:
			if (rndm < LowGoUp) {
				if (currentY < MaxBottomHeight) {
					currentY++;
					state = HIGH;
				}
				else {
					continue;
				}
			}
			else if (rndm >= LowGoUp && rndm < LowGoUp + LowGoDown) {
				if (currentY >= FilledBottomRows) {
					currentY--;
					state = LOW;
				}
				else {
					continue;
				}
			}
			else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					fillTilesBelow(currentX, currentY);
				}
				else {
					levelEndReached = true;
				}
			}
			break;
		}

		size_t current = currentY * LevelWidth + currentX;
		_level.at(current) = LevelGridTile(currentX, currentY, true);
	}
}

// fills the tiles below the given point with tiles
void LevelGrid::fillTilesBelow(int x, int y) {
	for (int i = 0; i < y; i++) {
		size_t current = x + i * LevelWidth;
		if (!_level.at(current).isGenerated()) {
			_level.at(current) = LevelGridTile(x, i, true);
		}
	}
}

void LevelGrid::addPlattforms() {
	int noOfPlattforms = rand() % MaxPlattforms + 1;
	std::vector<int> positions;

	for (int i = 0; i < noOfPlattforms; i++) {
		bool isUsableX = false;
		int x = 0, y = 0;

		do {
			x = rand() % (LevelWidth - StartingAreaWidth - EndAreaWidth - 2) + StartingAreaWidth + 2;

			if (positions.empty()) {
				isUsableX = true;
			}
			else {
				isUsableX = true;
				for (int j = 0; j < positions.size(); j++) {
					if (positions.at(j) == x) {
						isUsableX = false;
						break;
					}
				}
			}	

			y = MaxBottomHeight;
			size_t current = x + y * LevelWidth;
			while (!_level.at(current).isGenerated()) {
				current = x + --y * LevelWidth;
			}

			if (_level.at((x - 1) + (y + 1) * LevelWidth).isGenerated() ||
				_level.at((x + 1) + (y + 1) * LevelWidth).isGenerated() ||
				_level.at((x - 2) + (y + 1) * LevelWidth).isGenerated() ||
				_level.at((x + 2) + (y + 1) * LevelWidth).isGenerated()) {
				isUsableX = false;
			}
		} while (!isUsableX);

		positions.push_back(x - 1);
		positions.push_back(x);
		positions.push_back(x + 1);

		_level.at(x + (y + 2) * LevelWidth) = LevelGridTile(x, y + 2, true);
		_level.at((x - 1) + (y + 2) * LevelWidth) = LevelGridTile(x - 1, y + 2, true);
		_level.at((x + 1) + (y + 2) * LevelWidth) = LevelGridTile(x + 1, y + 2, true);
		_level.at(x + (y + 4) * LevelWidth) = LevelGridTile(x, y + 4, true);
	}
}

void LevelGrid::addPits() {
	int noOfPits = rand() % MaxPits + 1;
	std::vector<int> positions;

	for (int i = 0; i < noOfPits; i++) {
		bool isUsableX = false;
		int x = 0;

		do {
			x = rand() % (LevelWidth - StartingAreaWidth - EndAreaWidth - 2) + StartingAreaWidth;

			if (positions.empty()) {
				isUsableX = true;
			} else {
				isUsableX = true;
				for (int j = 0; j < positions.size(); j++) {
					if (positions.at(j) == x) {
						isUsableX = false;
						break;
					}
				}
			}
		} while (!isUsableX);

		positions.push_back(x - 1);
		positions.push_back(x);
		positions.push_back(x + 1);
		positions.push_back(x + 2);

		for (int pitX = x; pitX <= x + 1; pitX++) {
			int y = 0;
			while (_level.at(pitX + y * LevelWidth).isGenerated()) {
				_level.at(pitX + y * LevelWidth) = LevelGridTile(pitX, y, false);
				y++;
			}
		}		
	}
}

void LevelGrid::setTileBorders() {
	for (int currentX = 0; currentX < LevelWidth; currentX++) {
		for (int currentY = 0; currentY < LevelHeight; currentY++) {
			size_t current = currentX + currentY * LevelWidth;
			bool isBorder = false;

			if (currentX - 1 >= 0) {
				isBorder = !_level.at(current - 1).isFilled();
			} else {
				isBorder = true;
			}
			_level.at(current).setLeftBorder(isBorder);
			isBorder = false;

			if (currentX + 1 < LevelWidth) {
				isBorder = !_level.at(current + 1).isFilled();
			}
			else {
				isBorder = true;
			}
			_level.at(current).setRightBorder(isBorder);
			isBorder = false;

			if (currentY - 1 >= 0) {
				isBorder = !_level.at(current - LevelWidth).isFilled();
			}
			else {
				isBorder = true;
			}
			_level.at(current).setBottomBorder(isBorder);
			isBorder = false;

			if (currentY + 1 < LevelHeight) {
				isBorder = !_level.at(current + LevelWidth).isFilled();
			}
			else {
				isBorder = true;
			}
			_level.at(current).setTopBorder(isBorder);
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