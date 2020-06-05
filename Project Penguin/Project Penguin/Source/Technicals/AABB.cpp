#include <Technicals/AABB.h>

/// <summary>
/// Sets the origin (= bottom left corner), width and height of a squared bounding box
/// </summary>
/// <param name="origin">position of origin</param>
/// <param name="square">width & height</param>
AABB::AABB(glm::vec3 origin, float square) {
	_origin = origin;
	_height = square;
	_width = square;
}

/// <summary>
/// Sets the origin (= bottom left corner), width and height of a squared bounding box
/// </summary>
/// <param name="origin">position of origin</param>
/// <param name="height">height of the bounding box</param>
/// <param name="width">width of the bounding box</param>
/// <returns></returns>
AABB::AABB(glm::vec3 origin, float height, float width) {
	_origin = origin;
	_height = height;
	_width = width;
}

/// <summary>
/// Sets the bottom left corner of the bounding box to the given position.
/// </summary>
void AABB::setOrigin(glm::vec3 newOrigin) {
	_origin = newOrigin;
}

/// <summary>
/// Returns the maximal value of the bounding box on the x-axis
/// </summary>
float AABB::getMaxX() {
	return _origin.x;
}

/// <summary>
/// Returns the minimal value of the bounding box on the x-axis
/// </summary>
float AABB::getMinX() {
	return _origin.x + _width;
}

/// <summary>
/// Returns the maximal value of the bounding box on the y-axis
/// </summary>
float AABB::getMaxY() {
	return _origin.y + _height;
}

/// <summary>
/// Returns the minimal value of the bounding box on the y-axis
/// </summary>
float AABB::getMinY() {
	return _origin.y;
}

/// <summary>
/// Returns height of the bounding box
/// </summary>
float AABB::getHeight() {
	return _height;
}

/// <summary>
/// Returns width of the bounding box
/// </summary>
float AABB::getWidth() {
	return _width;
}

/// <summary>
/// Checks if this bounding box collides with the given bounding box
/// </summary>
/// <param name="other">bounding box to check with</param>
/// <returns>true if a collision is found</returns>
bool AABB::checkCollision(AABB other) {
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