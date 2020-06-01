#ifndef GRIDTILE_HEADER
#define GRIDTILE_HEADER

#include <GLM/glm.hpp>
#include <AABB.h>
#include <TileLocation.h>
#include <DrawableVertices.h>

class LevelGridTile : public DrawableVertices {
private:
	int _x{}, _y{}, _z = -10;
	float Size = 1.0f;

	bool _generated = false;
	bool _filled = false;
	bool _left = false;
	bool _right = false;
	bool _top = false;
	bool _bottom = false;

	TileLocation _loc = NORMAL;
	AABB _hitbox;

public:
	LevelGridTile();
	LevelGridTile(int x, int y);

	bool isGenerated();
	bool isFilled();
	void changeFilling(bool status);
	void changeLocation(TileLocation newLoc);

	void setLeftBorder(bool left);
	void setRightBorder(bool right);
	void setTopBorder(bool top);
	void setBottomBorder(bool bottom);
	unsigned char getBorderForTexture();

	glm::vec3 getPosition();
	AABB getHitbox();
	TileLocation getLocation();
};

#endif // GRIDTILE_HEADER