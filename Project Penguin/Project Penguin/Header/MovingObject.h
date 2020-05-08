#ifndef MOVINGOBJ_HEADER
#define MOVINGOBJ_HEADER

#include <GLM/glm.hpp>
#include <AABB.h>
#include <Texture.h>

enum MovingObjectStatus {
	STANDING,
	WALKING,
	JUMPING
};

class MovingObject {
private:
	const float Speed = 2.0f;

	glm::vec3 _position;
	AABB _hitbox;
	Texture _texture;
	MovingObjectStatus _status;
	
public:
	MovingObject(glm::vec3 pos, Texture texture);

	void Update();
};

#endif // MOVINGOBJ_HEADER
