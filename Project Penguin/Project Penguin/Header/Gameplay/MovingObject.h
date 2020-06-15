#ifndef MOVINGOBJ_HEADER
#define MOVINGOBJ_HEADER

#include <GLM/glm.hpp>
#include <IMoveable.h>
#include <IResetable.h>
#include <MovingObjectStatus.h>
#include <Technicals/AABB.h>
#include <Managers/GridFacade.h>

class MovingObject : public IMovable, public IResetable {
private:
	AABB _hitbox;

protected:
	static float Gravity;
	static float MaxFallingSpeed;

	MovingObjectStatus status = STAND;
	glm::vec3 position;

	bool wasOnGround = true;
	bool isOnGround = true;

	bool hasCeiling = false;
	bool hasTileLeft = false;
	bool hasTileRight = false;
	
	void update(float deltaTime);

	bool checkForPit(MovingObjectStatus dir);	
	bool checkForDoubleWall(MovingObjectStatus dir);
	bool checkForReachedArea(MovingObjectStatus dir, bool start);

public:
	static GridFacade* LevelFacade;

	MovingObject(glm::vec3 pos, AABB boundBox);

	void calculateSpeed(float deltaTime) override = 0;
	void reset() override;	
	
	AABB getHitbox();
	glm::vec3 getPosition();
	MovingObjectStatus getCurrentStatus();
};

#endif // MOVINGOBJ_HEADER