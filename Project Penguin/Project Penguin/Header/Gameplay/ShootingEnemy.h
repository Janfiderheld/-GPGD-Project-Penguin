#ifndef SHOOTENEMY_HEADER
#define SHOOTENEMY_HEADER

#include <Gameplay/Enemy.h>
#include <Gameplay/Projectile.h>
#include <Technicals/Texture.h>

class ShootingEnemy : public Enemy, public DrawableVertices {
private:
	static int MaxShootDistance;
	static int MinShootDistance;

	static glm::vec3 Scale;
	
	Projectile _currProj;
	AABB _killBox;
	glm::vec3 _killBoxPos;

	void updateKillingBox();

public:
	static Texture* ShooterTex;
	static glm::vec3 getScale();

	ShootingEnemy();
	ShootingEnemy(glm::vec3 pos, AABB boundBox);
	
	void shootProjectile(glm::vec3 playerPos);
	void setCurrentProjectile(Projectile proj);
	Projectile* getCurrentProjectile();
	AABB* getKillBox();
	
	void calculateSpeed(float deltaTime) override;
};

#endif // SHOOTENEMY_HEADER