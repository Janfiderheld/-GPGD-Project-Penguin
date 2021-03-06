#include <Level/LevelGrid.h>

/// <summary>
/// Creates a level by setting the seed for random numbers and generating the level
/// </summary>
LevelGrid::LevelGrid() {
	srand(time(NULL));
	generateWholeLevel();
}

/// <summary>
/// Fills the starting area, which has a defined size, with tiles.
/// </summary>
void LevelGrid::initializeStartingArea() {
	for (int y = 0; y <= FilledBottomRows; y++) {
		for (int x = 0; x <= StartingAreaWidth; x++) {
			size_t current = y * LevelWidth + x;
			_level.at(current) = LevelGridTile(x, y);
			if (y != FilledBottomRows) {
				_level.at(current).changeFilling(true);
			}
			if (y == FilledBottomRows - 1 && x != StartingAreaWidth) {
				_level.at(current).changeLocation(START_AREA);
			}			
		}
	}
}

/// <summary>
/// Generates the basic level with a finite state machine which can be found here:
/// .\Project Penguin\Assets\Documentation\LevelGenerationStateMachine.png
/// </summary>
void LevelGrid::generateBottom() {
	int currentX = StartingAreaWidth;
	int currentY = FilledBottomRows - 1;
	int countPlain = PlainWidth;

	while (true) {
		int rndm = rand() % 100;
		switch (state) {
		case LVL_START:
			if (rndm < SameGoUp && currentY < MaxBottomHeight) {
				currentY++;
				state = DOUBLE_HIGH;
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
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
			} else {
				state = LVL_END;
			}			
			break;

		case FINISHED_HIGH:
			if (rndm < HighGoUp) {
				if (currentY < MaxBottomHeight) {
					currentY++;
					state = DOUBLE_HIGH;
				}
			} else if (rndm >= HighGoUp && rndm < HighGoUp + HighGoDown) {
				if (currentY >= FilledBottomRows) {					
					currentY--;
					state = LOW;
				}			
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
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
				}
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					countPlain--;
					state = HIGH;
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
			if (currentX < LevelWidth - EndAreaWidth - 1) {
				currentX++;
				countPlain--;
			} else {
				state = LVL_END;
			}
			break;

		case FINISHED_LOW:
			if (rndm < LowGoUp) {
				if (currentY < MaxBottomHeight) {
					currentY++;
					state = HIGH;
				}
			} else if (rndm >= LowGoUp && rndm < LowGoUp + LowGoDown) {
				if (currentY >= FilledBottomRows) {
					currentY--;
					state = DOUBLE_LOW;
				}
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
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
				}
			} else {
				if (currentX < LevelWidth - EndAreaWidth - 1) {
					currentX++;
					countPlain--;
					state = LOW;
				} else {
					state = LVL_END;
				}
			}
			break;

		case LVL_END:
			deleteTilesAbove(currentX, currentY);

			if (currentX < LevelWidth - 1) {
				currentX++;
			} else {
				return;
			}
			break;
		}

		size_t current = currentY * LevelWidth + currentX;
		_level.at(current) = LevelGridTile(currentX, currentY);
		_level.at(current).changeFilling(true);
		fillTilesBelow(currentX, currentY);

		if (state == LVL_END) {
			_level.at(current).changeLocation(END_AREA);
		}
	}
}

/// <summary>
/// Fills all tiles below the given point.
/// </summary>
/// <param name="x">Position of starting tile on x-axis</param>
/// <param name="y">Position of starting tile on y-axis</param>
void LevelGrid::fillTilesBelow(int x, int y) {
	for (int i = y - 1; i >= 0; i--) {
		size_t current = x + i * LevelWidth;
		if (!_level.at(current).isFilled()) {
			_level.at(current) = LevelGridTile(x, i);
			_level.at(current).changeFilling(true);
		}
	}
}

/// <summary>
/// Deletes all tiles above the given point
/// </summary>
/// <param name="x">Position of starting tile on x-axis</param>
/// <param name="y">Position of starting tile on y-axis</param>
void LevelGrid::deleteTilesAbove(int x, int y) {
	for (int i = y + 1; i < LevelHeight; i++) {
		size_t current = x + i * LevelWidth;
		if (!_level.at(current).isFilled()) {
			_level.at(current).changeFilling(false);
		}
	}
}

/// <summary>
/// Adds a random number of plattforms to the finished level.
/// The amount is between 1 and (Width / 20). All Plattforms look the same.
/// </summary>
void LevelGrid::addPlattforms() {
	_platformsAmount = rand() % MaxPlattforms + 1;
	std::vector<int> positions;

	for (int i = 0; i < _platformsAmount; i++) {
		bool isUsableX = false;
		int x = 0, y = 0;

		do {
			x = generateRandomForPlacement() + 2;

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
		_level.at(x + (y + 2) * LevelWidth).changeFilling(true);

		_level.at((x - 1) + (y + 2) * LevelWidth) = LevelGridTile(x - 1, y + 2);
		_level.at((x - 1) + (y + 2) * LevelWidth).changeFilling(true);

		_level.at((x + 1) + (y + 2) * LevelWidth) = LevelGridTile(x + 1, y + 2);
		_level.at((x + 1) + (y + 2) * LevelWidth).changeFilling(true);

		_level.at(x + (y + 4) * LevelWidth) = LevelGridTile(x, y + 4);
		_level.at(x + (y + 4) * LevelWidth).changeFilling(true);
		_collectPos.push_back(glm::vec2(x, y + 5));
	}
}

/// <summary>
/// Adds a random number of pits to the finished level.
/// The amount is between 1 and (Width / 15). All pits are two tiles long.
/// </summary>
void LevelGrid::addPits() {
	_pitsAmount = rand() % MaxPits + 1;
	std::vector<int> positions;

	for (int i = 0; i < _pitsAmount; i++) {
		bool isUsableX = false;
		int x = 0;

		do {
			x = generateRandomForPlacement();

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

		positions.push_back(x - 2);
		positions.push_back(x - 1);
		positions.push_back(x);
		positions.push_back(x + 1);
		positions.push_back(x + 2);

		for (int pitX = x; pitX <= x + 1; pitX++) {
			int y = 0;
			while (_level.at(pitX + y * LevelWidth).isGenerated()) {
				_level.at(pitX + y * LevelWidth).changeFilling(false);
				y++;
			}
		}		
	}
}

/// <summary>
/// Iterates over the finished level and checks for each tile if the tile above is filled.
/// If so, that tile is marked, so the border can be drawn differently.
/// </summary>
void LevelGrid::setUpperTileBorders() {
	for (int currentX = 0; currentX < LevelWidth; currentX++) {
		for (int currentY = 0; currentY < LevelHeight; currentY++) {
			size_t current = currentX + currentY * LevelWidth;

			if (!_level.at(current).isFilled()) {
				continue;
			}

			if (currentY + 1 < LevelHeight) {
				_level.at(current).setTopBorder(!_level.at(current + LevelWidth).isFilled());
			} else {
				_level.at(current).setTopBorder(true);
			}
		}
	}
}

/// <summary>
/// Iterates over the finished level and generates all remaining tiles in the grid to 
/// circumvent errors of unset values.
/// </summary>
void LevelGrid::generateRemainingTiles() {
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

/// <summary>
/// Returns the tile in the level at the given position.
/// </summary>
/// <param name="x">Position of tile on x-axis</param>
/// <param name="y">Position of tile on y-axis</param>
LevelGridTile& LevelGrid::getTileFromGrid(int x, int y) {
	return _level.at(x + y * LevelWidth);
}

/// <summary>
/// Returns a reference to the vector containing the collectable positions on top of the platforms
/// </summary>
std::vector<glm::vec2>* LevelGrid::getCollectablePositions() {
	if (_generationFinished) {
		return &_collectPos;
	} else {
		return nullptr;
	}	
}

/// <summary>
/// Returns the current Number of Specials (pits or platforms)
/// </summary
int LevelGrid::getNumberOfSpecials() {
	return _pitsAmount + _platformsAmount;
}

/// <summary>
/// Returns width of the level
/// </summary>
int LevelGrid::getWidth() {
	return LevelWidth;
}

/// <summary>
/// Returns height of the level
/// </summary>
int LevelGrid::getHeight() {
	return LevelHeight;
}

/// <summary>
/// Generates the level grid.
/// The level has the dimension defined in its header.
/// First the Initialization is done the same way every time.
/// After that the procedural generation is based on a finite state machine.
/// Then platforms and pits are added.
/// After the level is finished, all tiles are checked if they are border tiles.
/// </summary>
void LevelGrid::generateWholeLevel() {
	_collectPos.clear();
	_level.clear();
	_level.resize(LevelHeight * LevelWidth);
	_generationFinished = false;
	state = LVL_START;

	initializeStartingArea();
	generateBottom();
	addPlattforms();
	addPits();

	generateRemainingTiles();
	setUpperTileBorders();
	_generationFinished = true;
}

/// <summary>
/// Generates a random number in the area where platforms, pits & collectables can be placed
/// </summary>
int LevelGrid::generateRandomForPlacement() {
	return rand() % (LevelWidth - StartingAreaWidth - EndAreaWidth - 2) + StartingAreaWidth;
}