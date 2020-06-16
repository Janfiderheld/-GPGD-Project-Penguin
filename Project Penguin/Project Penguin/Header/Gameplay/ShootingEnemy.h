#ifndef SHOOTENEMY_HEADER
#define SHOOTENEMY_HEADER

#include <Gameplay/MovingObject.h>
#include <Gameplay/Projectile.h>
#include <Technicals/Texture.h>

class ShootingEnemy : public MovingObject, public DrawableVertices {
private:
	static float JumpSpeed;
	static float WalkSpeed;
	static float SideSpeedAir;

	static int StandCountMax;
	static int MovementRadius;
	static int MaxShootDistance;
	static int MinShootDistance;

	static glm::vec3 Scale;
	
	int _standCounter = 0;
	bool _beforePit = false;
	bool _reachedSpecialArea = false;

	MovingObjectStatus _lastDir = WALK_LEFT;
	Projectile _currProj;

public:
	static Texture* ShooterTex;
	static glm::vec3 getScale();

	ShootingEnemy();
	ShootingEnemy(glm::vec3 pos, AABB boundBox);
	
	void shootProjectile(glm::vec3 playerPos);
	void setCurrentProjectile(Projectile proj);
	Projectile* getCurrentProjectile();
	
	void calculateSpeed(float deltaTime) override;
	void reset() override;
};

#endif // SHOOTENEMY_HEADER