#ifndef ENEMYMAN_HEADER
#define ENEMYMAN_HEADER

#include <vector>
#include <random>
#include <Gameplay/ShootingEnemy.h>
#include <Gameplay/WalkingEnemy.h>
#include <Gameplay/Projectile.h>
#include <Gameplay/Character.h>
#include <Managers/GridFacade.h>
#include <Technicals/AABB.h>

class EnemyManager {
private:
	static int MaxSpecialAmount;
	const int ShooterProb = 60;

	std::vector<ShootingEnemy> _shooters;
	std::vector<WalkingEnemy> _walkers;
	
	bool _currCollision = false;

public: 
	static GridFacade* LevelFacade;
	static Character* PlayerChar;	

	EnemyManager();

	void updateEnemies(float delta);	
	void generateEnemies();
	void checkForCollision();

	int getShooterAndProjectileAmount();
	int getWalkerAmount();
	ShootingEnemy* getShootingEnemyAtVectorPos(int pos);
	WalkingEnemy* getWalkingEnemyAtVectorPos(int pos);
	Projectile* getProjectileAtVectorPos(int pos);
};

#endif // ENEMYMAN_HEADER