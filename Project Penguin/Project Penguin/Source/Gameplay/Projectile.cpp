#include <Gameplay/Projectile.h>

/// <summary>
/// Distance of tiles until the projectile despawns
/// </summary>
int Projectile::MaxDistanceBeforeDestroy = 8;

/// <summary>
/// Speed with which the projectile moves through the world
/// </summary>
float Projectile::Speed = 2.0f;

/// <summary>
/// Texture for all projectiles
/// </summary>
Texture* Projectile::ProjectileTex = nullptr;

/// <summary>
/// Scale of the projectile
/// </summary>
glm::vec3 Projectile::Scale = glm::vec3(0.25f, 0.23f, 1.0f);

/// <summary>
/// Offset of the texture in relation to the origin.
/// Can be calculated by subtracting the Scale from 1 and dividing by two
/// </summary>
glm::vec2 Projectile::TextureOffset = glm::vec2(0.375f, 0.385f);

/// <summary>
/// Empty Constructor
/// </summary>
Projectile::Projectile() :
	MovingObject(getPosition(), getHitbox()),
	DrawableVertices(getHitbox().getMinX(), getHitbox().getMinY(), getHitbox().getMaxX(), getHitbox().getMaxY()) {
	changeStatus(true);
	setRadius(6);
	setColorAndBrightness(glm::vec4(1.0f, 1.0f, 1.0f, 0.6f));
}

/// <summary>
/// Constructor which sets the direction, the starting position and the bounding box
/// </summary>
/// <param name="pos">starting pos of this </param>
/// <param name="boundBox">hitbox for this projectile</param>
/// <param name="dir">direction in that this projectile starts</param>
Projectile::Projectile(glm::vec3 pos, AABB boundBox, MovingObjectStatus dir) :
	MovingObject(pos, AABB(pos, TextureOffset, Scale.y, Scale.x)),
	DrawableVertices(boundBox.getMinX(), boundBox.getMinY(), boundBox.getMaxX(), boundBox.getMaxY()) {
	if(dir != WALK_LEFT && dir != WALK_RIGHT) {
		_movDir = WALK_LEFT;
	}
	_movDir = dir;
	changeStatus(true);
	setRadius(6);
	setColorAndBrightness(glm::vec4(1.0f, 1.0f, 1.0f, 0.6f));
}

/// <summary>
/// Calculates the speed for this object & updates the position accordingly
/// </summary>
/// <param name="deltaTime">time since last frame</param>
void Projectile::calculateSpeed(float deltaTime) {
	if(!getStatus()) {
		return;
	}

	setHorizontalSpeed(_movDir == WALK_LEFT ? -Speed : Speed);
	updatePosition(deltaTime);
	shouldDeactivate();
}

/// <summary>
/// Returns a reference to the texture of this projectile
/// </summary>
Texture* Projectile::getTexture() {
	return ProjectileTex;
}

/// <summary>
/// Returns true if this projectile is active
/// </summary>
bool Projectile::getStatus() {
	return _isActive;
}

/// <summary>
/// Checks if this projectile object is inside the view frustum of the camera with the given view matrix.
/// This is used to optimize the performance and only calculate the position and collision for projectile who can be seen
///</summary>
/// <param name="view">view matrix of the camera</param>
/// <param name="proj">projection matrix of the application</param>
/// <returns>true if this projectile is inside the view frustum</returns>
bool Projectile::checkWithCameraArea(glm::mat4 view, glm::mat4 proj) {
	glm::vec4 posInClip = proj * view * glm::vec4(position, 1.0f);
	glm::vec3 posDehom = glm::vec3(posInClip.x / posInClip.w, posInClip.y / posInClip.w, posInClip.z / posInClip.w);

	if (posDehom.x <= 1.0f && posDehom.x >= -1.0f &&
		posDehom.y <= 1.0f && posDehom.y >= -1.0f) {
		return true;
	}

	_isActive = false;
	return false;
}

/// <summary>
/// Checks if this projectile should be disabled
/// </summary>
void Projectile::shouldDeactivate() {	
	if (abs(startPos.x - position.x) >= MaxDistanceBeforeDestroy || LevelFacade->checkForCollision(&getHitbox())){
		changeStatus(false);
	}
}

/// <summary>
/// Sets the status of this object to the given value
/// </summary>
void Projectile::changeStatus(bool state) {
	_isActive = state;
}

/// <summary>
/// Sets the position to the given position
/// </summary>
void Projectile::setPosition(glm::vec3 newPos) {
	position = newPos;
}

/// <summary>
/// Returns the position with the texture offset for fitting drawing
/// </summary>
glm::vec3 Projectile::getTexturePosition() {
	return glm::vec3(position.x - TextureOffset.x, position.y - TextureOffset.y, position.z);
}

/// <summary>
/// Changes the moving direction to the given value
/// </summary>
void Projectile::changeDirection(MovingObjectStatus dir) {
	if(dir != WALK_LEFT && dir != WALK_RIGHT) {
		_movDir = WALK_RIGHT;
	}

	_movDir = dir;
}