#ifndef AABB_HEADER
#define AABB_HEADER

#include <GLM/glm.hpp>

class AABB {
private:
	glm::vec3 _center;
public:
	AABB(glm::vec3 center);

	glm::vec3 getCenter();
	void setCenter(glm::vec3 newCenter);
};

#endif // AABB_HEADER