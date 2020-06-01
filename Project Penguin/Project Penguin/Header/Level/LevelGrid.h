#ifndef GRID_HEADER
#define GRID_HEADER

#include <vector>
#include <ctime>
#include <Level/LevelGridTile.h>
#include <LevelGenerationStates.h>

class LevelGrid {
private:
	// values for level generation
	const int LevelWidth = 60;
	const int LevelHeight = 15;
	const int FilledBottomRows = 3;
	const int StartingAreaWidth = 5;
	const int EndAreaWidth = 3;
	const int MaxBottomHeight = LevelHeight - 5;
	const int PlainWidth = 3;
	const int MaxPits = floor(LevelWidth / 15.0f);
	const int MaxPlattforms = ceil(LevelWidth / 20.0f);

	// probabilities for level generation
	const int SameGoUp = 30;
	const int HighGoUp = 20;
	const int HighGoDown = 30;
	const int LowGoUp = 30;
	const int LowGoDown = 20;
	const int DoubleHigh = 20;
	const int DoubleLow = 20;

	LevelGenerationStates state = LVL_START;
	std::vector<LevelGridTile> _level;

	void initializeStartingArea();
	void generateBottom();
	void addPlattforms();
	void addPits();

	void fillTilesBelow(int x, int y);
	void setTileBorders();
	void generateRemainingTiles();

public:
	LevelGrid();

	int getWidth();
	int getHeight();	

	LevelGridTile& getTileFromGrid(int x, int y);
};

#endif // GRID_HEADER