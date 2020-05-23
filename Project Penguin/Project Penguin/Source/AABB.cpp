#include "AABB.h"

AABB::AABB(glm::vec3 origin, int square)
{
	//AABB(origin, square, square);
	_origin = origin;
	_height = square;
	_width = square;
}

AABB::AABB(glm::vec3 origin, int height, int width)
{
	_origin = origin;
	_height = height;
	_width = width;
}

glm::vec3 AABB::getOrigin()
{
	return _origin;
}

void AABB::setOrigin(glm::vec3 newOrigin)
{
	_origin = newOrigin;
}

bool AABB::checkCollision(AABB other)
{
	if (_origin.x + _width < other._origin.x ||
		_origin.x > other._origin.x + other._width) {
		return false;
	} 
	if (_origin.y + _height < other._origin.y ||
		_origin.y > other._origin.y + other._height) {
		return false;
	}

	return true;
}
