#ifndef AABB_HEADER
#define AABB_HEADER

#include <GLM/glm.hpp>

class AABB {
private:
	glm::vec3 _origin;
	glm::vec2 _offset;
	
	float _height;
	float _width;
	bool _hasOffset;
	
public:
	AABB(glm::vec3 origin, float square);
	AABB(glm::vec3 origin, float height, float width);
	AABB(glm::vec3 origin, glm::vec2 offset, float height, float width);

	float getHeight();
	float getWidth();
	void setOrigin(glm::vec3 newOrigin);

	float getMaxX();
	float getMinX();
	float getMaxY();
	float getMinY();

	bool checkCollision(AABB other);
};

#endif // AABB_HEADER