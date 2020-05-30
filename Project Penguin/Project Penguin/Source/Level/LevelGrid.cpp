#include <Level/LevelGrid.h>

// Generates the level grid.
// The level has the dimension defined in its header.
// First the Initialization is done the same way every time.
// After that the procedural generation is based on a finite state machine.
// Then plattforms and pits are added.
// After the level is finished, all tiles are checked if they are border tiles.
LevelGrid::LevelGrid() {
	srand(time(NULL));

	size_t size = LevelHeight * LevelWidth;
	_level.resize(size);	

	initializeStartingArea();
	generateBottom();
	addPlattforms();
	addPits();

	generateRemainingTiles();
	setTileBorders();
}

// Fills the starting Area with tiles
void LevelGrid::initializeStartingArea() {
	for (int y = 0; y <= FilledBottomRows; y++) {
		for (int x = 0; x <= StartingAreaWidth; x++) {
			size_t current = y * LevelWidth + x;
			_level.at(current) = LevelGridTile(x, y);
			if (y != FilledBottomRows) {
				_level.at(current).fill();
			}
			if (y == FilledBottomRows - 1 && x != StartingAreaWidth) {
				_level.at(current).changeLocation(START_AREA);
			}			
		}
	}
}

// Generates the basic level with a finite state machine which can be found here:
// TODO: Add diagramm
void LevelGrid::generateBottom() {
	int currentX = StartingAreaWidth;
	int currentY = FilledBottomRows - 1;
	int countPlain = PlainWidth;
	bool levelEndReached = false;

	while (!levelEndReached) {
		int rndm = rand() % 100;
		switch (state) {
		case LVL_START:
			if (rndm < SameGoUp && currentY < MaxBottomHeight) {
				currentY++;
				state = DOUBLE_HIGH;
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					fillTilesBelow(currentX, currentY);
				} else {
					state = LVL_END;
				}
			}
			break;

		case HIGH:
			if (countPlain <= 0) {
				countPlain = PlainWidth;
				state = FINISHED_HIGH;
			}
			if (currentX < LevelWidth - EndAreaWidth - 1) {
				currentX++;
				countPlain--;
				fillTilesBelow(currentX, currentY);
			} else {
				state = LVL_END;
			}			
			break;

		case FINISHED_HIGH:
			if (rndm < HighGoUp) {
				if (currentY < MaxBottomHeight) {
					currentY++;
					state = DOUBLE_HIGH;
				} else {
					continue;
				}
			} else if (rndm >= HighGoUp && rndm < HighGoUp + HighGoDown) {
				if (currentY >= FilledBottomRows) {
					currentY--;
					state = LOW;
				} else {
					continue;
				}				
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					fillTilesBelow(currentX, currentY);
				} else {
					state = LVL_END;
				}
			}
			break;

		case DOUBLE_HIGH:
			if (rndm < DoubleHigh) {
				if (currentY < MaxBottomHeight) {
					currentY++;
					state = HIGH;
				} else {
					continue;
				}
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					countPlain--;
					state = HIGH;
					fillTilesBelow(currentX, currentY);
				} else {
					state = LVL_END;
				}
			}
			break;

		case LOW:
			if (countPlain <= 0) {
				countPlain = PlainWidth;
				state = FINISHED_LOW;
			}
			if (currentX < LevelWidth - EndAreaWidth) {
				currentX++;
				countPlain--;
				fillTilesBelow(currentX, currentY);
			} else {
				state = LVL_END;
			}
			break;

		case FINISHED_LOW:
			if (rndm < LowGoUp) {
				if (currentY < MaxBottomHeight) {
					currentY++;
					state = HIGH;
				} else {
					continue;
				}
			} else if (rndm >= LowGoUp && rndm < LowGoUp + LowGoDown) {
				if (currentY >= FilledBottomRows) {
					currentY--;
					state = DOUBLE_LOW;
				} else {
					continue;
				}
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					fillTilesBelow(currentX, currentY);
				} else {
					state = LVL_END;
				}
			}
			break;

		case DOUBLE_LOW:
			if (rndm < DoubleLow) {
				if (currentY >= FilledBottomRows) {
					currentY--;
					state = LOW;
				} else {
					continue;
				}
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					countPlain--;
					state = LOW;
					fillTilesBelow(currentX, currentY);
				} else {
					state = LVL_END;
				}
			}
			break;

		case LVL_END:
			if (currentX < LevelWidth - 1) {
				currentX++;
				fillTilesBelow(currentX, currentY);
			} else {
				levelEndReached = true;
			}
			break;
		}

		size_t current = currentY * LevelWidth + currentX;
		_level.at(current) = LevelGridTile(currentX, currentY);
		_level.at(current).fill();
		if (state == LVL_END) {
			_level.at(current).changeLocation(END_AREA);
		}
	}
}

// fills the tiles below the given point with tiles
void LevelGrid::fillTilesBelow(int x, int y) {
	for (int i = y - 1; i >= 0; i--) {
		size_t current = x + i * LevelWidth;
		_level.at(current) = LevelGridTile(x, i);
		_level.at(current).fill();
	}
}

// Adds a random number of plattforms to the finished level.
// The amount is between 1 and (Width / 20).
// All Plattforms look the same.
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

		_level.at(x + (y + 2) * LevelWidth) = LevelGridTile(x, y + 2);
		_level.at(x + (y + 2) * LevelWidth).fill();

		_level.at((x - 1) + (y + 2) * LevelWidth) = LevelGridTile(x - 1, y + 2);
		_level.at((x - 1) + (y + 2) * LevelWidth).fill();

		_level.at((x + 1) + (y + 2) * LevelWidth) = LevelGridTile(x + 1, y + 2);
		_level.at((x + 1) + (y + 2) * LevelWidth).fill();

		_level.at(x + (y + 4) * LevelWidth) = LevelGridTile(x, y + 4);
		_level.at(x + (y + 4) * LevelWidth).fill();
	}
}

// Adds a random number of pits to the finished level.
// The amount is between 1 and (Width / 15).
// All pits are two tiles long.
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
				_level.at(pitX + y * LevelWidth).empty();
				y++;
			}
		}		
	}
}

// Iterates over the finished level and checks for each tile which borders are not surrounded.
void LevelGrid::setTileBorders() {
	for (int currentX = 0; currentX < LevelWidth; currentX++) {
		for (int currentY = 0; currentY < LevelHeight; currentY++) {
			size_t current = currentX + currentY * LevelWidth;

			if (!_level.at(current).isFilled()) {
				continue;
			}

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

void LevelGrid::generateRemainingTiles()
{
	for (int currentX = 0; currentX < LevelWidth; currentX++) {
		for (int currentY = 0; currentY < LevelHeight; currentY++) {
			size_t current = currentX + currentY * LevelWidth;

			if (_level.at(current).isGenerated()) {
				continue;
			}

			_level.at(current) = LevelGridTile(currentX, currentY);
		}
	}
}

// Returns the tile at position (x, y).
LevelGridTile& LevelGrid::getTileFromGrid(int x, int y)
{
	return _level.at(x + y * LevelWidth);
}

// Returns the width of the level.
int LevelGrid::getWidth()
{
	return LevelWidth;
}

// Returns the height of the level.
int LevelGrid::getHeight()
{
	return LevelHeight;
}