#include <Gameplay/Character.h>

/// <summary>
/// Reference to the InputManager, which saves which key is pressed.
/// </summary>
InputManager* Character::InputManager = nullptr;

/// <summary>
/// Initializes the player character by setting the starting position, texture, bounding box and vertices.
/// </summary>
/// <param name="pos">starting position for the character</param>
/// <param name="texture">texture for the character</param>
/// <param name="boundBox">bounding box (= hitbox) for the character</param>
Character::Character(glm::vec3 pos, Texture texture, AABB boundBox) :
	MovingObject(pos, texture, boundBox),
	DrawableVertices(boundBox.getMinX(), boundBox.getMinY(), boundBox.getMaxX(), boundBox.getMaxY()) {
	_currentHealth = MaxHealth;
}

/// <summary>
/// Calculates the characters speed in the current frame by differentiating between the different movement states.
/// </summary>
/// <param name="deltaTime">time since last frame</param>
void Character::calculateSpeed(float deltaTime) {
	if(_rechedPitBottom || _reachedEnd)	{
		setCompleteSpeed(glm::vec3(0.0f));
		return;
	}
	
	switch (status)	{
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
			setHorizontalSpeed(-WalkSpeed);
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
			setHorizontalSpeed(WalkSpeed);
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
		setVerticalSpeed(JumpSpeed);
		status = FALL;
			
		break;	

	case FALL:
		setVerticalSpeed(speed.y + gravity * deltaTime);
		setVerticalSpeed(glm::max(speed.y, maxFallingSpeed));

		if (InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT) && !hasTileLeft) {
			setHorizontalSpeed(-SideSpeedAir);
		} else if(InputManager->getInputStatus(RIGHT) && !InputManager->getInputStatus(LEFT) && !hasTileRight) {
			setHorizontalSpeed(SideSpeedAir);
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

		checkForPitBottom();
		break;
	}

	checkForReachedEnd();
	update(deltaTime);
}

/// <summary>
/// Resets the character after a death
/// </summary>
void Character::reset() {
	MovingObject::reset();
	_rechedPitBottom = false;
	_currentHealth = MaxHealth;
}

/// <summary>
/// Checks if the player has reached a tile belonging to the ending area
/// </summary>
void Character::checkForReachedEnd() {
	int posX = floor(position.x);
	int posY = ceil(position.y) - 1;

	if (LevelFacade->checkForEndArea(posX, posY)) {
		_reachedEnd = true;
	}
}

/// <summary>
/// Checks if the player reached the bottom of a pit
/// </summary>
void Character::checkForPitBottom() {
	if(round(position.y) <= 0.0f) {
		_rechedPitBottom = true;
	}
}

/// <summary>
/// Returns true if the player has reached an ending tile
/// </summary>
bool Character::hasReachedEnd() {
	return _reachedEnd;
}

/// <summary>
/// Returns true if the character has died either by loosing all its health or by reaching the bottom of a pit
/// </summary>
bool Character::hasDied() {
	return _rechedPitBottom || _currentHealth <= 0;
}

/// <summary>
/// Makes the player loose a live, if possible
/// </summary>
void Character::looseHealth() {
	if(_currentHealth > 0) {
		_currentHealth--;
	}
}

/// <summary>
/// Returns the current health of the player
/// </summary>
int Character::getCurrentHealth() {
	return _currentHealth;
}

/// <summary>
/// Returns the maximal health of the player
/// </summary>
int Character::getMaxHealth() {
	return MaxHealth;
}