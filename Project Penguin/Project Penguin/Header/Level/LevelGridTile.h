#ifndef GRIDTILE_HEADER
#define GRIDTILE_HEADER

#include <GLM/glm.hpp>

class LevelGridTile {
private:
	static const int Size = 64;
	static const int VerticeAmount = 20;
	static const int IndexAmount = 6;

	float z = -10.0;

	int _x, _y;
	bool _filled = false;
	bool _generated = false;
	int _pit = 0;

	float* _vertices = new float[VerticeAmount];

public:
	LevelGridTile();
	LevelGridTile(int x, int y, bool filled);

	void addToPit(int pitNo);
	bool isFilled();
	bool isGenerated();

	float* getVertices();
	glm::vec3 getPosition();
};

#endif // GRIDTILE_HEADER
