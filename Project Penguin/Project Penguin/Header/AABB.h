#ifndef AABB_HEADER
#define AABB_HEADER

#include <GLM/glm.hpp>

class AABB {
private:
	glm::vec3 _origin;
	int _height;
	int _width;

public:
	AABB(glm::vec3 origin, int square);
	AABB(glm::vec3 origin, int height, int width);

	glm::vec3 getOrigin();
	void setOrigin(glm::vec3 newOrigin);

	bool checkCollision(AABB other);
};

#endif // AABB_HEADER