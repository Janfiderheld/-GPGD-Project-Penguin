#ifndef SHOOTENEMY_HEADER
#define SHOOTENEMY_HEADER

#include <Gameplay/MovingObject.h>

class ShootingEnemy : public MovingObject, public DrawableVertices {
private:
	const float JumpSpeed = 1.5f;
	const float WalkSpeed = 1.25f;
	const float SideSpeedAir = 0.85f;

	const int StandCountMax = 60;
	const int MovementRadius = 12;
	
	int _standCounter = 0;
	MovingObjectStatus _lastDir = WALK_LEFT;
	bool _beforePit = false;

	void shootProjectile();

public:
	ShootingEnemy(glm::vec3 pos, Texture texture, AABB boundBox);

	void calculateSpeed(float deltaTime) override;
	void reset() override;
};

#endif // SHOOTENEMY_HEADER