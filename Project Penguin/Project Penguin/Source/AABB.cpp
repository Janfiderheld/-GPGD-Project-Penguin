#include "AABB.h"

AABB::AABB(glm::vec3 origin, int square)
{
	AABB(origin, square, square);
}

AABB::AABB(glm::vec3 origin, int height, int width)
{
	_origin = origin;
	_height = height;
	_width = width;
}

// returns the position of the center
glm::vec3 AABB::getOrigin()
{
	return _origin;
}

// sets the position of the center
void AABB::setOrigin(glm::vec3 newOrigin)
{
	_origin = newOrigin;
}

// Returns the side of the collision
bool AABB::checkCollision(AABB other)
{
	if (_origin.x < other._origin.x + other._width &&
		_origin.x + _width > other._origin.x &&
		_origin.y < other._origin.y + other._height &&
		_origin.y + _height > other._origin.y + other._height) {
		return true;
	} else {
		return false;
	}
}
