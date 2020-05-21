#ifndef GRID_HEADER
#define GRID_HEADER

#include <vector>
#include <Level/LevelGridTile.h>
#include <Texture.h>
#include <time.h>

#define START		0
#define HIGH		1
#define HIGH_FIN	2
#define LOW			3
#define LOW_FIN		4

class LevelGrid {
private:
	static const int LevelWidth = 60;
	static const int LevelHeight = 14;

	// TODO: Refine values when movement is implemented
	const float Friction = 2.0f;
	const float Gravity = 2.0f;

	// values for level generation
	const int FilledBottomRows = 3;
	const int StartingAreaWidth = 5;
	const int EndAreaWidth = 3;
	const int MaxBottomHeight = LevelHeight - 4;
	const int PlainWidth = 3;
	const int MaxPits = floor(LevelWidth / 15.0f);
	const int MaxPlattforms = ceil(LevelWidth / 20.0f);

	// probabilities for level generation
	const int SameGoUp = 30;
	const int HighGoUp = 20;
	const int HighGoDown = 30;
	const int LowGoUp = 30;
	const int LowGoDown = 20;

	int state = START;

	// Access via [currentY * width + currentX]
	std::vector<LevelGridTile> _level;

	void initializeGrid();
	void generateBottom();
	void fillTilesBelow(int x, int y);
	void addPlattforms();
	void addPits();

	void setTileBorders();

public:
	LevelGrid();

	void drawGrid(Texture txt);

	LevelGridTile getTileFromGrid(int x, int y);

	int getWidth();
	int getHeight();	
};

#endif // GRID_HEADER
