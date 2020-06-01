#ifndef MOVINGOBJ_HEADER
#define MOVINGOBJ_HEADER

#include <GLM/glm.hpp>
#include <IMoveable.h>
#include <MovingObjectStatus.h>
#include <AABB.h>
#include <Texture.h>
#include <Level/GridFacade.h>


class MovingObject : public IMovable {
private:
	AABB _hitbox;
	Texture _texture;	

protected:
	const float gravity = -0.85f;
	const float maxFallingSpeed = -2.75f;

	MovingObjectStatus status = STAND;
	glm::vec3 position;

	bool wasOnGround = true;
	bool isOnGround = true;

	bool hasCeiling = false;
	bool hasTileLeft = false;
	bool hasTileRight = false;
	
public:
	static GridFacade* LevelFacade;

	MovingObject(glm::vec3 pos, Texture texture, AABB boundBox);

	virtual void calculateSpeed(float deltaTime) = 0;
	void Update(float deltaTime);

	AABB getHitbox();
	Texture getTexture();
	glm::vec3 getPosition();
	MovingObjectStatus getCurrentStatus();
};

#endif // MOVINGOBJ_HEADER