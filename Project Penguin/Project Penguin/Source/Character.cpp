#include <Character.h>

Character::Character(glm::vec3 pos, Texture texture, AABB boundBox) : MovingObject(pos, texture, boundBox)
{
}

void Character::calculatePosition(float deltaTime)
{
	switch (status)
	{
	case STANDING:
		setCompleteSpeed(glm::vec3(0.0f));
		if (!isOnGround) {
			status = JUMPING;
		} else if (getInputStatus(LEFT) || getInputStatus(RIGHT)) {
			status = WALKING;
		} else if (getInputStatus(UP)) {
			setVerticalSpeed(_jumpSpeed);
			status = JUMPING;
		}
		break;

	case WALKING:
		if (!getInputStatus(LEFT) && !getInputStatus(RIGHT)) {
			status = STANDING;
			setCompleteSpeed(glm::vec3(0.0f));
		} else if (getInputStatus(LEFT)) {
			setHorizontalSpeed(hasTileLeft ? 0.0f : -_walkSpeed);
		} else if (getInputStatus(RIGHT)) {
			setHorizontalSpeed(hasTileRight ? 0.0f : _walkSpeed);
		} else if (getInputStatus(UP)) {
			setVerticalSpeed(_jumpSpeed);
			status = JUMPING;
		} else if (!isOnGround) {
			status = JUMPING;
		}
		break;

	case JUMPING:
		setVerticalSpeed(speed.y + gravity * deltaTime);
		setVerticalSpeed(glm::max(speed.y, maxFallingSpeed));

		if (getInputStatus(LEFT)) {
			setHorizontalSpeed(hasTileLeft ? 0.0f : -_walkSpeed);
		} else if (getInputStatus(RIGHT)) {
			setHorizontalSpeed(hasTileRight ? 0.0f : _walkSpeed);
		} 

		if (isOnGround && !wasOnGround) {
			if (!getInputStatus(LEFT) && !getInputStatus(RIGHT)) {
				status = STANDING;
				setCompleteSpeed(glm::vec3(0.0f));
			} else {
				status = WALKING;
				setVerticalSpeed(0.0f);
			}
		}
		break;
	}

	UpdatePhysics(deltaTime);
}