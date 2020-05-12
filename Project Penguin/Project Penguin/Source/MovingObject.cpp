#include <MovingObject.h>

// Constructor, which sets the texture and the position
MovingObject::MovingObject(glm::vec3 pos, Texture texture) : _texture(texture), _hitbox(pos)
{
	_position = pos;
	_status = STANDING;
}

// Moves the object
void MovingObject::Update() {
	// TODO: Add moving functionality
}

void MovingObject::calculatePosition(MovementDirection dir, float deltaTime) {
	float velocity = getSpeed() * deltaTime;
}