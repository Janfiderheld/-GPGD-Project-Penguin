#include <Character.h>

Character::Character(glm::vec3 pos, Texture texture, AABB boundBox) : MovingObject(pos, texture, boundBox)
{
}

void Character::calculatePosition(float deltaTime)
{
	switch (status)
	{
	case STAND:
		setCompleteSpeed(glm::vec3(0.0f));

		if (getInputStatus(LEFT)) {
			status = WALK_LEFT;
			break;
		} 
		if (getInputStatus(RIGHT)) {
			status = WALK_RIGHT;
			break;
		}
		if ((getInputStatus(UP) && !hasCeiling) || !isOnGround) {
			status = JUMP;
			_isFalling = !isOnGround;
			break;
		}

		break;

	case WALK_LEFT:
		setVerticalSpeed(0.0f);

		if (hasTileLeft) {
			status = STAND;
			break;
		} else {
			setHorizontalSpeed(-_walkSpeed);
		}
		if (getInputStatus(RIGHT)) {
			status = WALK_RIGHT;
			break;
		}
		if (!getInputStatus(LEFT)) {
			status = STAND;
			break;
		} 
		if ((getInputStatus(UP) && !hasCeiling) || !isOnGround) {
			status = JUMP;
			_isFalling = !isOnGround;
			break;
		}

		break;

	case WALK_RIGHT:
		setVerticalSpeed(0.0f);

		if (hasTileRight) {
			status = STAND;
			break;
		} else {
			setHorizontalSpeed(_walkSpeed);
		}
		if (getInputStatus(LEFT)) {
			status = WALK_LEFT;
			break;
		}
		if (!getInputStatus(RIGHT)) {
			status = STAND;
			break;
		}
		if ((getInputStatus(UP) && !hasCeiling) || !isOnGround) {
			status = JUMP;
			_isFalling = !isOnGround;
			break;
		}

		break;

	case JUMP:
		if (!_isFalling) {
			setVerticalSpeed(_jumpSpeed);
			_isFalling = true;
		} 	
		setVerticalSpeed(speed.y + gravity * deltaTime);
		setVerticalSpeed(glm::max(speed.y, maxFallingSpeed));
		// TODO: Clip speed when tile is above
		if (getInputStatus(LEFT)) {
			setHorizontalSpeed(hasTileLeft ? 0.0f : -_sideSpeedAir);
		} else if (getInputStatus(RIGHT)) {
			setHorizontalSpeed(hasTileRight ? 0.0f : _sideSpeedAir);
		}

		if (isOnGround && !wasOnGround) {
			if (!getInputStatus(LEFT) && !getInputStatus(RIGHT)) {
				status = STAND;
				break;
			} 
			if (getInputStatus(LEFT)) {
				status = WALK_LEFT;
				break;
			}
			if (getInputStatus(RIGHT)) {
				status = WALK_RIGHT;
				break;
			}
		}

		break;
	}

	UpdatePhysics(deltaTime);
}