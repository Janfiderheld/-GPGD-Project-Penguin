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
/// Minimum counter to see how long an enemy keeps standing
/// </summary>
int Enemy::StandCountMin = 60;

/// <summary>
/// Maxmimum counter to see how long an enemy keeps standing
/// </summary>
int Enemy::StandCountMax = 120;

/// <summary>
/// Counting towards this number when no movement in x-direction is done and resetting the character as a fall back.
/// </summary>
int Enemy::StandCountError = 230;

/// <summary>
/// Maximum amount of tiles in any direction the enemy can move from its starting position
/// </summary>
int Enemy::MovementRadius = 12;

/// <summary>
/// Describes the area of the View Frustum (in NDC) in which calculations are allowed
/// </summary>
float Enemy::FrustumCullingRadius = 1.1f;

/// <summary>
/// Sets the position and the hitbox box
/// </summary>
/// <param name="pos">starting position for this enemy</param>
/// <param name="boundBox">hitbox for this enemy</param>
Enemy::Enemy(glm::vec3 pos, AABB boundBox) : MovingObject(pos, boundBox) {
	_standCounterMax = rand() % (StandCountMax - StandCountMin) + StandCountMin;
	_posLastFrame = pos.x;
}

/// <summary>
/// Calculates the current position and speed of the player
/// </summary>
/// <param name="deltaTime">time since last frame update</param>
void Enemy::calculateSpeed(float deltaTime) {
	_beforePit = checkForPit(status);
	_reachedStart = checkForReachedArea(status, true);
	_reachedEnd = checkForReachedArea(status, false);
	float distToRightTile = floor(position.x) + 1 - getHitbox().getMaxX();

	switch (status) {
	case STAND:
		setCompleteSpeed(glm::vec3(0.0f));

		if (_standCounter >= _standCounterMax) {
			if(_reachedStart || _lastDir == WALK_LEFT) {
				status = WALK_RIGHT;
			}
			if(_reachedEnd || _lastDir == WALK_RIGHT) {
				status = WALK_LEFT;
			}
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

		if (!hasTileLeft && !_beforePit && startPos.x - position.x <= MovementRadius &&
			!_reachedStart && !checkForDoubleWall(WALK_LEFT)) {
			setHorizontalSpeed(-WalkSpeed);
		} else if (hasTileLeft && !checkForDoubleWall(WALK_LEFT) && startPos.x - position.x <= MovementRadius) {
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

		if ((!hasTileRight && !_beforePit) || distToRightTile >= 0.0f && position.x - startPos.x <= MovementRadius &&
			!_reachedEnd && !checkForDoubleWall(WALK_RIGHT)) {
			setHorizontalSpeed(WalkSpeed);
		} else if (hasTileRight && !checkForDoubleWall(WALK_RIGHT) && position.x - startPos.x <= MovementRadius) {
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
		setVerticalSpeed(speed.y + Gravity * deltaTime);
		setVerticalSpeed(glm::max(speed.y, MaxFallingSpeed));

		if (_lastDir == WALK_LEFT && !hasTileLeft &&
			!checkForPit(WALK_LEFT) && startPos.x - position.x <= MovementRadius &&
			!_reachedStart) {
			setHorizontalSpeed(-SideSpeedAir);
		} else if (_lastDir == WALK_RIGHT && (!hasTileRight && !checkForPit(WALK_RIGHT)) || distToRightTile >= 0.0f
			&& position.x - startPos.x <= MovementRadius &&
			!_reachedEnd) {
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

/// <summary>
/// Checks if this enemy object is inside the view frustum of the camera with the given view matrix.
/// This is used to optimize the performance and only calculate the position and collision for enemies who can be seen/// <summary>
/// <param name="view">view matrix of the camera</param>
/// <param name="proj">projection matrix of the application</param>
/// <returns>true if this enemy is inside the view frustum</returns>
bool Enemy::checkWithCameraArea(glm::mat4 view, glm::mat4 proj) {
	glm::vec4 posInClip = proj * view * glm::vec4(position, 1.0f);
	glm::vec3 posDehom = glm::vec3(posInClip.x / posInClip.w, posInClip.y / posInClip.w, posInClip.z / posInClip.w);

	if (posDehom.x <= FrustumCullingRadius && posDehom.x >= -FrustumCullingRadius &&
		posDehom.y <= FrustumCullingRadius && posDehom.y >= -FrustumCullingRadius) {
		return true;
	}

	return false;
}

/// <summary>
/// Returns true when the enemies last direction was left
/// </summary>
bool Enemy::checkLastDirectionLeft(){
	switch (status)
	{
	case WALK_LEFT:
		return true;
		break;

	case WALK_RIGHT:
		return false;
		break;

	case STAND:
	case JUMP:
	case FALL:
	default:
		return _lastDir == WALK_LEFT;
		break;
	}
}