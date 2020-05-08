#include <MovingObject.h>

MovingObject::MovingObject(glm::vec3 pos, Texture texture) : _texture(texture), _hitbox(pos)
{
	_position = pos;
	_status = STANDING;
}

void MovingObject::Update() {
	// TODO: Add moving functionality
}