#ifndef CHAR_HEADER
#define CHAR_HEADER

#include <MovingObject.h>

class Character : public MovingObject {
private:
	const float _jumpSpeed = 1.25f;
	const float _walkSpeed = 1.5f;
	const float _sideSpeedAir = 0.5;

	float* _vertices = new float[20];

public:
	Character(glm::vec3 pos, Texture texture, AABB boundBox);

	virtual void calculatePosition(float deltaTime);
	float* getVertices();
};

#endif // CHAR_HEADER
