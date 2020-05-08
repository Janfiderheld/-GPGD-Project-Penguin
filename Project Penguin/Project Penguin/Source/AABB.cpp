#include "AABB.h"

AABB::AABB(glm::vec3 center)
{
	_center = center;
}

glm::vec3 AABB::getCenter()
{
	return _center;
}

void AABB::setCenter(glm::vec3 newCenter)
{
	_center = newCenter;
}