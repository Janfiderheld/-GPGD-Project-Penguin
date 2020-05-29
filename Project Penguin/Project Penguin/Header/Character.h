#ifndef CHAR_HEADER
#define CHAR_HEADER

#include <MovingObject.h>

class Character : public MovingObject {
private:
	const float _jumpSpeed = 1.0f;
	const float _walkSpeed = 1.5f;
	const float _sideSpeedAir = 0.5;

	bool _isFalling = false;

public:
	Character(glm::vec3 pos, Texture texture, AABB boundBox);

	virtual void calculatePosition(float deltaTime);
};

#endif // CHAR_HEADER
