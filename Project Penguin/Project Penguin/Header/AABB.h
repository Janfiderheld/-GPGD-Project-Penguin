#ifndef AABB_HEADER
#define AABB_HEADER

#include <GLM/glm.hpp>

class AABB {
private:
	glm::vec3 _origin;
	float _height;
	float _width;

public:
	AABB(glm::vec3 origin, float square);
	AABB(glm::vec3 origin, float height, float width);

	glm::vec3 getOrigin();
	void setOrigin(glm::vec3 newOrigin);

	float getHeight();
	float getWidth();

	bool checkCollision(AABB other);
};

#endif // AABB_HEADER