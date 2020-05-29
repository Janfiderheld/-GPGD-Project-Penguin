#ifndef GRIDTILE_HEADER
#define GRIDTILE_HEADER

#include <GLM/glm.hpp>
#include <AABB.h>

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

	int _x, _y;
	float z = -10.0;

	bool _generated = false;
	bool _filled = false;
	bool _left = false;
	bool _right = false;
	bool _top = false;
	bool _bottom = false;

	Location _loc = NORMAL;
	AABB _hitbox;

	float* _vertices = new float[VerticeAmount];

public:
	LevelGridTile();
	LevelGridTile(int x, int y);

	void fill();
	void empty();
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
	AABB getHitbox();
};

#endif // GRIDTILE_HEADER
