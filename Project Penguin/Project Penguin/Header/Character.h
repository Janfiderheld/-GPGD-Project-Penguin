#ifndef CHAR_HEADER
#define CHAR_HEADER

#include <MovingObject.h>
#include <InputManager.h>
#include <DrawableVertices.h>

class Character : public MovingObject, public DrawableVertices {
private:
	const float _jumpSpeed = 2.0f;
	const float _walkSpeed = 2.0f;
	const float _sideSpeedAir = 1.25f;

	bool _reachedEnd = false;
	void checkForReachedEnd();

public:
	static InputManager* InputManager;

	Character(glm::vec3 pos, Texture texture, AABB boundBox);

	virtual void calculateSpeed(float deltaTime);
	
	bool hasReachedEnd();
};

#endif // CHAR_HEADER