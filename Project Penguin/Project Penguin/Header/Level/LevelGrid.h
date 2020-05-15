#ifndef GRID_HEADER
#define GRID_HEADER

#include <vector>
#include <Level/LevelGridTile.h>
#include <Texture.h>
#include <time.h>

class LevelGrid {
private:
	static const int LevelWidth = 20;
	static const int LevelHeight = 5;

	// TODO: Refine values when movement is implemented
	const float Friction = 2.0f;
	const float Gravity = 2.0f;

	// values for level generation
	const int FilledBottomRows = 3;
	const int StartingAreaWidth = 5;

	// Access via [currentY * width + currentX]
	std::vector<LevelGridTile> _level;

	void initializeGrid();
	void generateBorder();
	void fillGrid();

public:
	LevelGrid();

	void drawGrid(Texture txt);

	LevelGridTile getTileFromGrid(int x, int y);

	int getWidth();
	int getHeight();	
};

#endif // GRID_HEADER
