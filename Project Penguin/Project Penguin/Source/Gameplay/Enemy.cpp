#include <Gameplay/Enemy.h>

/// <summary>
/// Initial speed in y direction for jumping
/// </summary>
float Enemy::JumpSpeed = 1.5f;

/// <summary>
/// speed for walking in x direction
/// </summary>
float Enemy::WalkSpeed = 1.25f;

/// <summary>
/// speed for moving the object in x direction in the air
/// </summary>
float Enemy::SideSpeedAir = 0.85f;

/// <summary>
/// Counting towards this number to see how long an enemy keeps standing
/// </summary>
int Enemy::StandCountMax = 60;

/// <summary>
/// Counting towards this number when no movement in x-direction is done and resetting the character as a fall back.
/// </summary>
int Enemy::StandCountError = 230;

/// <summary>
/// Maximum amount of tiles in any direction the enemy can move from its starting position
/// </summary>
int Enemy::MovementRadius = 12;

/// <summary>
/// Sets the position and the hitbox box
/// </summary>
/// <param name="pos">starting position for this enemy</param>
/// <param name="boundBox">hitbox for this enemy</param>
Enemy::Enemy(glm::vec3 pos, AABB boundBox) : MovingObject(pos, boundBox) {
}

/// <summary>
/// Calculates the current position and speed of the player
/// </summary>
/// <param name="deltaTime">time since last frame update</param>
void Enemy::calculateSpeed(float deltaTime) {
	_beforePit = checkForPit(status);
	_reachedSpecialArea = checkForReachedArea(status, true) || checkForReachedArea(status, false);

	switch (status) {
	case STAND:
		setCompleteSpeed(glm::vec3(0.0f));

		if (_standCounter >= StandCountMax) {
			status = _lastDir == WALK_LEFT ? WALK_RIGHT : WALK_LEFT;
			_standCounter = 0;
			break;
		}
		else {
			_standCounter++;
		}
		if (!isOnGround) {
			status = FALL;
			break;
		}

		break;

	case WALK_LEFT:
		setVerticalSpeed(0.0f);

		if (!hasTileLeft && !_beforePit && startPos.x - position.x <= MovementRadius &&
			!_reachedSpecialArea && !checkForDoubleWall(WALK_LEFT)) {
			setHorizontalSpeed(-WalkSpeed);
		}
		else if (hasTileLeft && !checkForDoubleWall(WALK_LEFT) && startPos.x - position.x <= MovementRadius) {
			_lastDir = WALK_LEFT;
			status = JUMP;
			break;
		}
		else {
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

		if (!hasTileRight && !_beforePit && position.x - startPos.x <= MovementRadius &&
			!_reachedSpecialArea && !checkForDoubleWall(WALK_RIGHT)) {
			setHorizontalSpeed(WalkSpeed);
		}
		else if (hasTileRight && !checkForDoubleWall(WALK_RIGHT) && position.x - startPos.x <= MovementRadius) {
			_lastDir = WALK_RIGHT;
			status = JUMP;
			break;
		}
		else {
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
		setVerticalSpeed(speed.y + Gravity * deltaTime);
		setVerticalSpeed(glm::max(speed.y, MaxFallingSpeed));

		if (_lastDir == WALK_LEFT && !hasTileLeft &&
			!checkForPit(WALK_LEFT) && startPos.x - position.x <= MovementRadius &&
			!_reachedSpecialArea) {
			setHorizontalSpeed(-SideSpeedAir);
		}
		else if (_lastDir == WALK_RIGHT && !hasTileRight &&
			!checkForPit(WALK_RIGHT) && position.x - startPos.x <= MovementRadius &&
			!_reachedSpecialArea) {
			setHorizontalSpeed(SideSpeedAir);
		}
		else {
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
			if (hasTileLeft || hasTileRight) {
				status = JUMP;
				break;
			}
			if (checkForPit(_lastDir)) {
				status = STAND;
				break;
			}
		}
		break;
	}

	updateBoundaries(deltaTime);
	if(abs(_posLastFrame - position.x) <= 0.1f) {
		_errorCounter++;
	}
	_posLastFrame = position.x;
	if(_errorCounter >= StandCountError) {
		status = STAND;
		_errorCounter = 0;
	}
}