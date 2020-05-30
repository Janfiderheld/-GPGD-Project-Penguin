#ifndef CHAR_HEADER
#define CHAR_HEADER

#include <MovingObject.h>

class Character : public MovingObject {
private:
	const float _jumpSpeed = 2.0f;
	const float _walkSpeed = 2.0f;
	const float _sideSpeedAir = 1.25f;

	float* _vertices = new float[20];

public:
	Character(glm::vec3 pos, Texture texture, AABB boundBox);

	virtual void calculatePosition(float deltaTime);
	float* getVertices();
};

#endif // CHAR_HEADER
