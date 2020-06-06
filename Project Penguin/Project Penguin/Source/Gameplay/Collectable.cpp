#include <Gameplay/Collectable.h>

/// <summary>
/// Points the player gets for collecting a single collectable
/// </summary>
int Collectable::ScoreValue = 10;

/// <summary>
/// Scale of a collectable
/// </summary>
glm::vec3 Collectable::Scale = glm::vec3(0.8f, 0.4f, 1.0f);

/// <summary>
/// Texture to use for drawing the collectable
/// </summary>
Texture* Collectable::CollectTex = nullptr;

/// <summary>
/// Creates the bounding box & the vertices based on the tiles position 
/// </summary>
Collectable::Collectable() :
	DrawableVertices(_position.x, _position.y, _position.x + Scale.x, _position.y + Scale.y),
	_hitbox(getPosition(), Scale.x, Scale.y)
{
	// empty constructor
}

/// <summary>
/// Sets the bounding box, the position and the texture of this object to the given values
/// </summary>
/// <param name="pos">starting position</param>
/// <param name="boundBox">bounding box for the collectable</param>
Collectable::Collectable(glm::vec2 pos) :
	DrawableVertices(pos.x, pos.y, pos.x + Scale.x, pos.y + Scale.y),
	_hitbox(getPosition(), Scale.x, Scale.y)
{
	_position = glm::vec3(pos, _z);
	_hitbox = AABB(getPosition(), Scale.x, Scale.y);
}

/// <summary>
/// Returns the bounding box of the collectable
/// </summary>
AABB Collectable::getHitbox() {
	return _hitbox;
}

/// <summary>
/// Returns the position of the collectable
/// </summary>
glm::vec3 Collectable::getPosition() {
	return _position;
}

/// <summary>
/// Returns the scale of this collectable in all directions
/// </summary>
glm::vec3 Collectable::getScale() {
	return Scale;
}

/// <summary>
/// Returns the score, which this collectable gives the player
/// </summary>
int Collectable::getScore() {
	return ScoreValue;
}

/// <summary>
/// Checks if this collectable is already collected
/// </summary>
bool Collectable::isCollected() {
	return _isCollected;
}

/// <summary>
/// Marks this collectable as collected, so it is ignored in the future
/// </summary>
void Collectable::collect() {
	_isCollected = true;
}