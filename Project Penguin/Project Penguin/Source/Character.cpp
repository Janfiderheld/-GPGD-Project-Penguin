#include <Character.h>

InputManager* Character::InputManager = nullptr;

Character::Character(glm::vec3 pos, Texture texture, AABB boundBox) : MovingObject(pos, texture, boundBox) {

}

void Character::calculatePosition(float deltaTime) {
	switch (status)
	{
	case STAND:
		setCompleteSpeed(glm::vec3(0.0f));

		if (InputManager->getInputStatus(LEFT)) {
			status = WALK_LEFT;
			break;
		} 
		if (InputManager->getInputStatus(RIGHT)) {
			status = WALK_RIGHT;
			break;
		}
		if (InputManager->getInputStatus(UP) && !hasCeiling) {
			status = JUMP;
			break;
		}
		if (!isOnGround) {
			status = FALL;
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
		if (InputManager->getInputStatus(RIGHT)) {
			status = WALK_RIGHT;
			break;
		}
		if (!InputManager->getInputStatus(LEFT)) {
			status = STAND;
			break;
		} 
		if (InputManager->getInputStatus(UP) && !hasCeiling) {
			status = JUMP;
			break;
		}
		if (!isOnGround) {
			status = FALL;
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
		if (InputManager->getInputStatus(LEFT)) {
			status = WALK_LEFT;
			break;
		}
		if (!InputManager->getInputStatus(RIGHT)) {
			status = STAND;
			break;
		}
		if (InputManager->getInputStatus(UP) && !hasCeiling) {
			status = JUMP;
			break;
		}
		if(!isOnGround) {
			status = FALL;
			break;
		}

		break;

	case JUMP:
		setVerticalSpeed(_jumpSpeed);
		status = FALL;
			
		break;	

	case FALL:
		setVerticalSpeed(speed.y + gravity * deltaTime);
		setVerticalSpeed(glm::max(speed.y, maxFallingSpeed));

		if (InputManager->getInputStatus(LEFT) && !hasTileLeft) {
			setHorizontalSpeed(-_sideSpeedAir);
		} else if(InputManager->getInputStatus(RIGHT) && !hasTileRight) {
			setHorizontalSpeed(_sideSpeedAir);
		} else {
			setHorizontalSpeed(0.0f);
		}

		if (isOnGround && !wasOnGround) {
			if (!InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT)) {
				status = STAND;
				break;
			}
			if (InputManager->getInputStatus(LEFT)) {
				status = WALK_LEFT;
				break;
			}
			if (InputManager->getInputStatus(RIGHT)) {
				status = WALK_RIGHT;
				break;
			}
			if (InputManager->getInputStatus(UP)) {
				status = JUMP;
				break;
			}
		}

		break;
	}

	UpdatePhysics(deltaTime);
	InputManager->Update();
	checkForReachedEnd();
}

float* Character::getVertices() {
	// TODO: Find a possiblity to use a loop
	_vertices[0] = (float)getHitbox().getMaxX();
	_vertices[1] = (float)getHitbox().getMaxY();
	_vertices[2] = getPosition().z;
	_vertices[3] = 1.0f;
	_vertices[4] = 1.0f;
	_vertices[5] = (float)getHitbox().getMaxX();
	_vertices[6] = (float)getHitbox().getMinY();
	_vertices[7] = getPosition().z;
	_vertices[8] = 1.0f;
	_vertices[9] = 0.0f;
	_vertices[10] = (float)getHitbox().getMinX();
	_vertices[11] = (float)getHitbox().getMinY();
	_vertices[12] = getPosition().z;
	_vertices[13] = 0.0f;
	_vertices[14] = 0.0f;
	_vertices[15] = (float)getHitbox().getMinX();
	_vertices[16] = (float)getHitbox().getMaxY();
	_vertices[17] = getPosition().z;;
	_vertices[18] = 0.0f;
	_vertices[19] = 1.0f;

	return _vertices;
}

void Character::checkForReachedEnd() {
	int posX = floor(position.x);
	int posY = ceil(position.y) - 1;

	if (Facade->checkForEndArea(posX, posY)) {
		status = STAND;
		_reachedEnd = true;
	}
}

bool Character::hasReachedEnd() {
	return _reachedEnd;
}
