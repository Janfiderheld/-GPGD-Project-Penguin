#include "AABB.h"

AABB::AABB(glm::vec3 origin, float square)
{
	_origin = origin;
	_height = square;
	_width = square;
}

AABB::AABB(glm::vec3 origin, float height, float width)
{
	_origin = origin;
	_height = height;
	_width = width;
}

void AABB::setOrigin(glm::vec3 newOrigin)
{
	_origin = newOrigin;
}

float AABB::getMaxX()
{
	return _origin.x;
}

float AABB::getMinX()
{
	return _origin.x + _width;
}

float AABB::getMaxY()
{
	return _origin.y + _height;
}

float AABB::getMinY()
{
	return _origin.y;
}

float AABB::getHeight()
{
	return _height;
}

float AABB::getWidth()
{
	return _width;
}

bool AABB::checkCollision(AABB other)
{
	if (getMaxX() < other.getMinX() ||
		getMinX() > other.getMaxX()) {
		return false;
	} 
	if (getMaxY() < other.getMinY() ||
		getMinY() > other.getMaxY()) {
		return false;
	}

	return true;
}