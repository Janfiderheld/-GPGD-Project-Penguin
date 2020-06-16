#include <Gameplay/ShootingEnemy.h>

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
	Enemy(position, getHitbox()),
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
	Enemy(pos, boundBox),
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
	Enemy::calculateSpeed(deltaTime);
	_currProj.calculateSpeed(deltaTime);
	updateKillingBox();
}