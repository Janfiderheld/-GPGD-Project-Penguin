#include <Character.h>

/// <summary>
/// Reference to the InputManager, which saves which key is pressed.
/// </summary>
InputManager* Character::InputManager = nullptr;

/// <summary>
/// Initializes the player character by setting the starting position, texture and bounding box.
/// </summary>
/// <param name="pos">starting position for the character</param>
/// <param name="texture">texture for the character</param>
/// <param name="boundBox">bounding box (= hitbox) for the character</param>
Character::Character(glm::vec3 pos, Texture texture, AABB boundBox) : MovingObject(pos, texture, boundBox) {
}

/// <summary>
/// Calculates the characters speed in the current frame by differentiating between the different movement states.
/// </summary>
/// <param name="deltaTime">time since last frame</param>
void Character::calculateSpeed(float deltaTime) {
	switch (status)
	{
	case STAND:
		setCompleteSpeed(glm::vec3(0.0f));

		if (InputManager->getInputStatus(RIGHT) && !InputManager->getInputStatus(LEFT)) {
			status = WALK_RIGHT;
			break;
		}
		if (InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT)) {
			status = WALK_LEFT;
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

		if (!hasTileLeft) {
			setHorizontalSpeed(-_walkSpeed);
		}
		if (InputManager->getInputStatus(LEFT) && InputManager->getInputStatus(RIGHT) ||
			!InputManager->getInputStatus(LEFT) || hasTileLeft) {
			status = STAND;
			break;
		}
		if (InputManager->getInputStatus(RIGHT) && !InputManager->getInputStatus(LEFT)) {
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

	case WALK_RIGHT:
		setVerticalSpeed(0.0f);

		if (!hasTileRight) {
			setHorizontalSpeed(_walkSpeed);
		}
		if (InputManager->getInputStatus(LEFT) && InputManager->getInputStatus(RIGHT) ||
			!InputManager->getInputStatus(RIGHT) || hasTileRight) {
			status = STAND;
			break;
		}
		if (InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT)) {
			status = WALK_LEFT;
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

		if (InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT) && !hasTileLeft) {
			setHorizontalSpeed(-_sideSpeedAir);
		} else if(InputManager->getInputStatus(RIGHT) && !InputManager->getInputStatus(LEFT) && !hasTileRight) {
			setHorizontalSpeed(_sideSpeedAir);
		} else {
			setHorizontalSpeed(0.0f);
		}

		if (isOnGround && !wasOnGround) {
			if (!InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT) ||
				InputManager->getInputStatus(LEFT) && InputManager->getInputStatus(RIGHT)) {
				status = STAND;
				break;
			}
			if (InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT)) {
				status = WALK_LEFT;
				break;
			}
			if (InputManager->getInputStatus(RIGHT) && !InputManager->getInputStatus(LEFT)) {
				status = WALK_RIGHT;
				break;
			}
			if (InputManager->getInputStatus(UP) && !hasCeiling) {
				status = JUMP;
				break;
			}
		}

		break;
	}

	Update(deltaTime);
	checkForReachedEnd();
}

/// <summary>
/// Returns the vertices to draw the player character
/// </summary>
float* Character::getVertices() {
	// TODO: Find a possibility to use a loop
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

/// <summary>
/// Checks if the player has reached a tile belonging to the ending area
/// </summary>
void Character::checkForReachedEnd() {
	int posX = floor(position.x);
	int posY = ceil(position.y) - 1;

	if (LevelFacade->checkForEndArea(posX, posY)) {
		status = STAND;
		_reachedEnd = true;
	}
}

/// <summary>
/// Returns true if the player has reached an ending tile
/// </summary>
bool Character::hasReachedEnd() {
	return _reachedEnd;
}