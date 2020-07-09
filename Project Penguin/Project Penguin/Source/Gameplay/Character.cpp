#include <Gameplay/Character.h>

/// <summary>
/// Scale of the character
/// </summary>
glm::vec3 Character::Scale = glm::vec3(0.56f, 0.85f, 1.0f);

/// <summary>
/// Offset of the texture in relation to the origin.
/// Can be calculated by subtracting the Scale from 1 and dividing by two
/// </summary>
glm::vec2 Character::TextureOffset = glm::vec2(0.22f, 0.075f);

/// <summary>
/// Initial speed in y direction for jumping
/// </summary>
float Character::JumpSpeed = 2.0f;

/// <summary>
/// speed for walking in x direction
/// </summary>
float Character::WalkSpeed = 2.0f;

/// <summary>
/// speed for moving the object in x direction in the air
/// </summary>
float Character::SideSpeedAir = 1.25f;

/// <summary>
/// Maximal Health of the player
/// </summary>
int Character::MaxHealth = 3;

/// <summary>
/// Points the player gets for each remaining heart at the end of the level
/// </summary>
int Character::PointsPerHeart = 10;

/// <summary>
/// Reference to the InputManager, which saves which key is pressed.
/// </summary>
InputManager* Character::InputManager = nullptr;

/// <summary>
/// Returns the scale of the character
/// </summary>
glm::vec3 Character::getScale() {
	return Scale;
}

/// <summary>
/// Initializes the player character by setting the starting position, texture, bounding box and vertices.
/// </summary>
/// <param name="pos">starting position for the character</param>
/// <param name="texture">texture for the character</param>
/// <param name="boundBox">bounding box (= hitbox) for the character</param>
Character::Character(glm::vec3 pos, Texture* texture, AABB boundBox) :
	MovingObject(pos, boundBox),
	DrawableVertices(boundBox.getMinX(), boundBox.getMinY(), boundBox.getMaxX(), boundBox.getMaxY()) {
	_currentHealth = MaxHealth;
	_tex = texture;
}

/// <summary>
/// Calculates the characters speed in the current frame by differentiating between the different movement states.
/// </summary>
/// <param name="deltaTime">time since last frame</param>
void Character::calculateSpeed(float deltaTime) {
	_atLeftLevelEnd = position.x <= 0.5f;
	_atRightLevelEnd = position.x >= LevelFacade->getLevelWidth() - 1;
	float distToRightTile = floor(position.x) + 1 - getHitbox().getMaxX();

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
		_lastDir = WALK_LEFT;

		if (!hasTileLeft) {
			setHorizontalSpeed(-WalkSpeed);
		}
		if(_atLeftLevelEnd) {
			setHorizontalSpeed(0.0f);
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
		_lastDir = WALK_RIGHT;

		if (!hasTileRight || distToRightTile >= 0.0f) {
			setHorizontalSpeed(WalkSpeed);
		} else {
			setHorizontalSpeed(0.0f);
		}
		if(_atRightLevelEnd) {
			setHorizontalSpeed(0.0f);
		}

		if (InputManager->getInputStatus(LEFT) && InputManager->getInputStatus(RIGHT) ||
			!InputManager->getInputStatus(RIGHT)) {
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
		setVerticalSpeed(speed.y + Gravity * deltaTime);
		setVerticalSpeed(glm::max(speed.y, MaxFallingSpeed));

		if (InputManager->getInputStatus(LEFT) && !InputManager->getInputStatus(RIGHT) && !hasTileLeft && !_atLeftLevelEnd) {
			setHorizontalSpeed(-SideSpeedAir);
			_lastDir = WALK_LEFT;
		} else if(InputManager->getInputStatus(RIGHT) && !InputManager->getInputStatus(LEFT) && !_atRightLevelEnd) {
			if (!hasTileRight || distToRightTile >= 0.0f) {
				setHorizontalSpeed(SideSpeedAir);
				_lastDir = WALK_RIGHT;
			} else {	
				setHorizontalSpeed(0.0f);
			}
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

	_reachedEnd = checkForReachedArea(WALK_RIGHT, false);
	updateBoundaries(deltaTime);
}

/// <summary>
/// Resets the character after a death
/// </summary>
void Character::reset() {
	MovingObject::reset();
	_reachedPitBottom = false;
	_reachedEnd = false;
	_atLeftLevelEnd = false;
	_atRightLevelEnd = false;
	_currentHealth = MaxHealth;
}

/// <summary>
/// Checks if the player reached the bottom of a pit
/// </summary>
void Character::checkForPitBottom() {
	if(round(position.y) <= 0.0f) {
		_reachedPitBottom = true;
	}
}

/// <summary>
/// Returns true if the player has reached an ending tile
/// </summary>
bool Character::hasReachedEnd() {
	return _reachedEnd && isOnGround;
}

/// <summary>
/// Returns true if the character was last facing left
/// </summary>
bool Character::checkLastDirectionLeft() {
	if (_lastDir != WALK_LEFT && _lastDir != WALK_RIGHT) {
		return false;
	}

	return _lastDir == WALK_LEFT;
}

/// <summary>
/// Returns true if the character has died either by loosing all its health or by reaching the bottom of a pit
/// </summary>
bool Character::hasDied() {
	return _reachedPitBottom || _currentHealth <= 0;
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
/// Kills the player instantly by setting its current health to 0
/// </summary>
void Character::dieInstantly() {
	_currentHealth = 0;
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

/// <summary>
/// Returns the Texture for the main character
/// </summary>
Texture* Character::getTexture() {
	return _tex;
}

/// <summary>
/// Returns the position with the texture offset for fitting drawing
/// </summary>
glm::vec3 Character::getTexturePosition() {
	return glm::vec3(position.x - TextureOffset.x, position.y - TextureOffset.y, position.z);
}
