#include <Gameplay/ShootingEnemy.h>

/// <summary>
/// Initial speed in y direction for jumping
/// </summary>
float ShootingEnemy::JumpSpeed = 1.5f;

/// <summary>
/// speed for walking in x direction
/// </summary>
float ShootingEnemy::WalkSpeed = 1.25f;

/// <summary>
/// speed for moving the object in x direction in the air
/// </summary>
float ShootingEnemy::SideSpeedAir = 0.85f;

/// <summary>
/// Counting towards this number to see how long an enemy keeps standing
/// </summary>
int ShootingEnemy::StandCountMax = 60;

/// <summary>
/// Maximum amount of tiles in any direction the enemy can move from its starting position
/// </summary>
int ShootingEnemy::MovementRadius = 12;

/// <summary>
/// Maximum distance of the player to this object before shooting
/// </summary>
int ShootingEnemy::MaxShootDistance = 5;

/// <summary>
/// Minimum distance of the player to this object before shooting
/// </summary>
int ShootingEnemy::MinShootDistance = 2;

/// <summary>
/// Scale of all shooting enemies
/// </summary>
glm::vec3 ShootingEnemy::Scale = glm::vec3(0.65f, 0.9f, 1.0f);

/// <summary>
/// Texture for the shooting enemy
/// </summary>
Texture* ShootingEnemy::ShooterTex = nullptr;

/// <summary>
/// Empty constructor for the vector
/// </summary>
ShootingEnemy::ShootingEnemy() : 
	MovingObject(position, getHitbox()),
	DrawableVertices(getHitbox().getMinX(), getHitbox().getMinY(), getHitbox().getMaxX(), getHitbox().getMaxY()),
	_killBox(glm::vec3(position.x, position.y + Scale.y, position.z), 0.1f, Scale.x / 2.0f) {
	updateKillingBox();
}

/// <summary>
/// Initializes a shooting enemy by setting the starting position, texture, bounding box and vertices.
/// </summary>
/// <param name="pos">starting position for the enemy</param>
/// <param name="boundBox">bounding box (= hitbox) for the character</param>
ShootingEnemy::ShootingEnemy(glm::vec3 pos, AABB boundBox) :
	MovingObject(pos, boundBox),
	DrawableVertices(boundBox.getMinX(), boundBox.getMinY(), boundBox.getMaxX(), boundBox.getMaxY()),
	_killBox(glm::vec3(position.x, position.y + Scale.y, position.z), 0.1f, Scale.x / 2.0f) {
	_currProj = Projectile(pos, AABB(pos, Projectile::Scale.y, Projectile::Scale.x), WALK_RIGHT);
	_currProj.changeStatus(false);
	updateKillingBox();
}

/// <summary>
/// Shoots projectile in the direction this enemy is looking when certain criteria are met
/// </summary>
void ShootingEnemy::shootProjectile(glm::vec3 playerPos) {
	if (_currProj.getStatus()) {
		return;
	}
	
	bool shootLeft = speed.x < 0;
	if(speed.x == 0) {
		shootLeft = _lastDir == WALK_LEFT;
	}

	float dist = shootLeft ? position.x - playerPos.x : playerPos.x - position.x;
	if(dist > MinShootDistance && dist < MaxShootDistance) {
		_currProj.changeDirection(shootLeft ? WALK_LEFT : WALK_RIGHT);
		_currProj.setPosition(position);
		_currProj.changeStatus(true);
	}
}

/// <summary>
/// Sets the reference of the current projectile to the given pointer
/// </summary>
void ShootingEnemy::setCurrentProjectile(Projectile proj) {
	_currProj = proj;
}

/// <summary>
/// Returns a reference to the current Projectile
/// </summary>
Projectile* ShootingEnemy::getCurrentProjectile() {
	return &_currProj;
}

/// <summary>
/// Returns the hitbox which is above this object for killing it
/// </summary>
AABB* ShootingEnemy::getKillBox() {
	return &_killBox;
}

/// <summary>
/// Updates the position of the hitbox used to kill this enemy
/// </summary>
void ShootingEnemy::updateKillingBox() {
	_killBoxPos = position;
	_killBoxPos.y += Scale.y;
	_killBoxPos.x += Scale.x / 2.0f;
	_killBox.setOrigin(_killBoxPos);
}

/// <summary>
/// Returns the scale of a shooting enemy
/// </summary>
glm::vec3 ShootingEnemy::getScale() {
	return Scale;
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

		if (!hasTileLeft && !_beforePit && startPos.x - position.x <= MovementRadius &&
			!_reachedSpecialArea && !checkForDoubleWall(WALK_LEFT)) {
			setHorizontalSpeed(-WalkSpeed);
		} else if(hasTileLeft && !checkForDoubleWall(WALK_LEFT) && startPos.x - position.x <= MovementRadius) {
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

		if (!hasTileRight && !_beforePit && position.x - startPos.x <= MovementRadius &&
			!_reachedSpecialArea && !checkForDoubleWall(WALK_RIGHT)) {
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
			!_reachedSpecialArea) {
			setHorizontalSpeed(-SideSpeedAir);
		} else if (_lastDir == WALK_RIGHT && !hasTileRight &&
			!checkForPit(WALK_RIGHT) && position.x - startPos.x <= MovementRadius &&
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
	_currProj.calculateSpeed(deltaTime);
	updateKillingBox();
}

/// <summary>
/// Resets this object for a new game
/// </summary>
void ShootingEnemy::reset() {
	MovingObject::reset();
	_lastDir = WALK_LEFT;
	_beforePit = false;
}