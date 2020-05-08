#include "AABB.h"

// Constructor which sets the center of the bounding box
AABB::AABB(glm::vec3 center)
{
	_center = center;
}

// returns the position of the center
glm::vec3 AABB::getCenter()
{
	return _center;
}

// sets the position of the center
void AABB::setCenter(glm::vec3 newCenter)
{
	_center = newCenter;
}