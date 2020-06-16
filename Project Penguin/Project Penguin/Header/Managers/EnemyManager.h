#ifndef ENEMYMAN_HEADER
#define ENEMYMAN_HEADER

#include <vector>
#include <random>
#include <Gameplay/ShootingEnemy.h>
#include <Gameplay/Projectile.h>
#include <Gameplay/Character.h>
#include <Managers/GridFacade.h>
#include <Technicals/UserInterface.h>
#include <Technicals/AABB.h>

class EnemyManager {
private:
	const int ShooterProb = 60;

	bool _currentlyColliding = false;
	std::vector<ShootingEnemy> _shooters;

public: 
	static GridFacade* LevelFacade;
	static Character* PlayerChar;

	EnemyManager();

	void updateEnemies(float delta);	
	void generateEnemies();
	void checkForCollision();

	int getShooterAndProjectileAmount();
	ShootingEnemy* getShootingEnemyAtVectorPos(int pos);
	Projectile* getProjectileAtVectorPos(int pos);
};

#endif // ENEMYMAN_HEADER