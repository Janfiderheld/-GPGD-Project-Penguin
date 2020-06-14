#include <Gameplay/ShootingEnemy.h>

/// <summary>
/// Shoots projectile in the direction this enemy is looking when certain criteria are met
/// </summary>
void ShootingEnemy::shootProjectile() {
}

/// <summary>
/// Initializes a shooting enemy by setting the starting position, texture, bounding box and vertices.
/// </summary>
/// <param name="pos">starting position for the character</param>
/// <param name="texture">texture for the character</param>
/// <param name="boundBox">bounding box (= hitbox) for the character</param>
ShootingEnemy::ShootingEnemy(glm::vec3 pos, Texture texture, AABB boundBox) :
	MovingObject(pos, texture, boundBox),
	DrawableVertices(boundBox.getMinX(), boundBox.getMinY(), boundBox.getMaxX(), boundBox.getMaxY()) {
}

/// <summary>
/// Calculates the Movement speed based on the current status
/// </summary>
/// <param name="deltaTime">time since the last frame</param>
void ShootingEnemy::calculateSpeed(float deltaTime) {
	_beforePit = checkForPit(status);
	_reachedSpecialArea = checkForReachedArea(status, true) || checkForReachedArea(status, false);

	switch (status) {
	case STAND:
		setCompleteSpeed(glm::vec3(0.0f));

		if (_standCounter >= StandCountMax) {
			status = _lastDir == WALK_LEFT ? WALK_RIGHT : WALK_LEFT;
			_standCounter = 0;
			break;
		} else {
			_standCounter++;
		}
		if (!isOnGround) {
			status = FALL;
			break;
		}

		break;

	case WALK_LEFT:
		setVerticalSpeed(0.0f);

		if (!hasTileLeft && !_beforePit && (startPos.x - position.x) <= MovementRadius 
			&& !_reachedSpecialArea && !checkForDoubleWall(WALK_LEFT)) {
			setHorizontalSpeed(-WalkSpeed);
		} else if(hasTileLeft && !checkForDoubleWall(WALK_LEFT)) {
			_lastDir = WALK_LEFT;
			status = JUMP;
			break;
		} else {
			_lastDir = WALK_LEFT;
			status = STAND;
			break;
		}

		if (!isOnGround) {
			_lastDir = WALK_LEFT;
			status = FALL;
			break;
		}
		break;

	case WALK_RIGHT:
		setVerticalSpeed(0.0f);

		if (!hasTileRight && !_beforePit && (position.x - startPos.x) <= MovementRadius 
			&& !_reachedSpecialArea && !checkForDoubleWall(WALK_RIGHT)) {
			setHorizontalSpeed(WalkSpeed);
		} else if (hasTileRight && !checkForDoubleWall(WALK_RIGHT)) {
			_lastDir = WALK_RIGHT;
			status = JUMP;
			break;
		} else {
			_lastDir = WALK_RIGHT;
			status = STAND;
			break;
		}
		if (!isOnGround) {
			_lastDir = WALK_RIGHT;
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

		if (_lastDir == WALK_LEFT && !hasTileLeft &&
			!checkForPit(WALK_LEFT) && (startPos.x - position.x) <= MovementRadius &&
			!_reachedSpecialArea) {
			setHorizontalSpeed(-SideSpeedAir);
		} else if (_lastDir == WALK_RIGHT && !hasTileRight &&
			!checkForPit(WALK_RIGHT) && (position.x - startPos.x) <= MovementRadius &&
			!_reachedSpecialArea) {
			setHorizontalSpeed(SideSpeedAir);
		} else {
			setHorizontalSpeed(0.0f);
		}		

		if (isOnGround && !wasOnGround) {
			if (_lastDir == WALK_LEFT && !hasTileLeft) {
				status = WALK_LEFT;
				break;
			}
			if (_lastDir == WALK_RIGHT && !hasTileRight) {
				status = WALK_RIGHT;
				break;
			}
			if (checkForPit(_lastDir)) {
				status = STAND;
				break;
			}
			if (hasTileLeft || hasTileRight) {
				status = JUMP;
				break;
			}
		}		
		break;
	}
	update(deltaTime);
}

/// <summary>
/// Resets this object for a new game
/// </summary>
void ShootingEnemy::reset() {
	MovingObject::reset();
	_lastDir = WALK_LEFT;
	_beforePit = false;
}