#ifndef MOVINGOBJ_HEADER
#define MOVINGOBJ_HEADER

#include <IMoveable.h>
#include <GLM/glm.hpp>
#include <AABB.h>
#include <Texture.h>
#include <Level/GridFacade.h>
#include <MovingObjectStatus.h>

class MovingObject : public IMovable {
private:
	AABB _hitbox;
	Texture _texture;	

protected:
	const float gravity = -0.5;
	const float maxFallingSpeed = -2.0f;

	glm::vec3 position;
	glm::vec3 oldPosition;
	MovingObjectStatus status = STAND;

	bool wasOnGround = true;
	bool isOnGround = true;
	bool hasCeiling = false;

	bool hasTileLeft = false;
	bool hadTileLeft = false;
	bool hasTileRight = false;
	bool hadTileRight = false;

	bool currInputs[3];
	bool prevInputs[3];
	
public:
	MovingObject(glm::vec3 pos, Texture texture, AABB boundBox);

	static GridFacade* Facade;

	virtual void calculatePosition(float deltaTime) = 0;
	void UpdatePhysics(float deltaTime);

	AABB getHitbox();
	Texture getTexture();
	glm::vec3 getPosition();

	bool justPressed(Direction keyDirect);
	bool justReleased(Direction keyDirect);
	bool getInputStatus(Direction keyDirect);
	void setInputStatus(Direction keyDirect, bool val);
};

#endif // MOVINGOBJ_HEADER