#ifndef MOVINGOBJ_HEADER
#define MOVINGOBJ_HEADER

#include <GLM/glm.hpp>
#include <AABB.h>
#include <Texture.h>
#include <IMoveable.h>

enum MovingObjectStatus {
	STANDING,
	WALKING,
	JUMPING
};

class MovingObject : public IMovable {
private:
	glm::vec3 _position;
	AABB _hitbox;
	Texture _texture;
	MovingObjectStatus _status;
	
public:
	MovingObject(glm::vec3 pos, Texture texture);

	void Update();

	virtual void calculatePosition(MovementDirection dir, float deltaTime);
};

#endif // MOVINGOBJ_HEADER