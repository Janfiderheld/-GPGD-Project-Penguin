#ifndef GRIDTILE_HEADER
#define GRIDTILE_HEADER

#include <GLM/glm.hpp>

enum Location {
	NORMAL,
	START_AREA,
	END_AREA
};

class LevelGridTile {
private:
	static const int Size = 64;
	static const int VerticeAmount = 20;
	static const int IndexAmount = 6;

	float z = -10.0;

	bool _left = false, _right = false, _top = false, _bottom = false;

	int _x, _y;
	bool _filled = false;
	bool _generated = false;
	Location _loc = NORMAL;

	float* _vertices = new float[VerticeAmount];

public:
	LevelGridTile();
	LevelGridTile(int x, int y, bool filled);

	bool isFilled();
	bool isGenerated();

	void changeLocation(Location newLoc);
	Location getLocation();

	void setLeftBorder(bool left);
	void setRightBorder(bool right);
	void setTopBorder(bool top);
	void setBottomBorder(bool bottom);
	unsigned char getBorderForTexture();

	float* getVertices();
	glm::vec3 getPosition();
};

#endif // GRIDTILE_HEADER
