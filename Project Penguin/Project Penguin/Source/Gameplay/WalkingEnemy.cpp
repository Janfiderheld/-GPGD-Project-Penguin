#include <Gameplay/WalkingEnemy.h>

/// <summary>
/// Scale of all walking enemies
/// </summary>
glm::vec3 WalkingEnemy::Scale = glm::vec3(0.6f, 0.46f, 1.0f);

/// <summary>
/// Offset of the texture in relation to the origin.
/// Can be calculated by subtracting the Scale from 1 and dividing by two
/// </summary>
glm::vec2 WalkingEnemy::TextureOffset = glm::vec2(0.2f, 0.28f);

/// <summary>
/// Texture for the walking enemy
/// </summary>
Texture* WalkingEnemy::WalkerTex = nullptr;

/// <summary>
/// Returns the scale of the walking enemies
/// </summary>
glm::vec3 WalkingEnemy::getScale() {
	return Scale;
}

/// <summary>
/// Empty constructor for the vector
/// </summary>
WalkingEnemy::WalkingEnemy() :
	Enemy(position, getHitbox()),
	DrawableVertices(getHitbox().getMinX(), getHitbox().getMinY(), getHitbox().getMaxX(), getHitbox().getMaxY()) {
	
}

/// <summary>
/// Initializes a walking enemy by setting the starting position, texture, bounding box and vertices.
/// </summary>
/// <param name="pos">starting position for the enemy</param>
/// <param name="boundBox">bounding box (= hitbox) for the character</param>
WalkingEnemy::WalkingEnemy(glm::vec3 pos, AABB boundBox) :
	Enemy(pos, boundBox),
	DrawableVertices(boundBox.getMinX(), boundBox.getMinY(), boundBox.getMaxX(), boundBox.getMaxY()) {
	
}

/// <summary>
/// Returns the position with the texture offset for fitting drawing
/// </summary>
glm::vec3 WalkingEnemy::getTexturePosition() {
	return glm::vec3(position.x - TextureOffset.x, position.y - TextureOffset.y, position.z);
}

/// <summary>
/// Updates the boundaries for the walking enemy specifically
/// </summary>
/// <param name="deltaTime">time since last frame</param>
void WalkingEnemy::updateBoundaries(float deltaTime){
	MovingObject::updateBoundaries(deltaTime);
	if (status == FALL) {
		hasTileRight = LevelFacade->checkForWall(floor(position.x) + 1, floor(position.y));
	}
}