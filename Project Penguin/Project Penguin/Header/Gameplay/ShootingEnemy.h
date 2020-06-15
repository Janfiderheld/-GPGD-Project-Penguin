#ifndef SHOOTENEMY_HEADER
#define SHOOTENEMY_HEADER

#include <Gameplay/MovingObject.h>
#include <Technicals/Texture.h>

class ShootingEnemy : public MovingObject, public DrawableVertices {
private:
	static float JumpSpeed;
	static float WalkSpeed;
	static float SideSpeedAir;

	static int StandCountMax;
	static int MovementRadius;
	
	int _standCounter = 0;
	MovingObjectStatus _lastDir = WALK_LEFT;
	bool _beforePit = false;
	bool _reachedSpecialArea = false;

	void shootProjectile();

public:
	static Texture* ShooterTex;

	ShootingEnemy();
	ShootingEnemy(glm::vec3 pos, AABB boundBox);

	void calculateSpeed(float deltaTime) override;
	void reset() override;
};

#endif // SHOOTENEMY_HEADER