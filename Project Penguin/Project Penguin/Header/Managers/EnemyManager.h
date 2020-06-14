#ifndef ENEMYMAN_HEADER
#define ENEMYMAN_HEADER

#include <vector>
#include <random>
#include <Gameplay/ShootingEnemy.h>
#include <Managers/GridFacade.h>
#include <Technicals/UserInterface.h>
#include <Technicals/AABB.h>

class EnemyManager {
private:
	const int ShooterProb = 60;

	std::vector<ShootingEnemy> _shooters;

public: 
	static GridFacade* LevelFacade;

	EnemyManager();

	void generateEnemys();
	void checkForCollision(AABB playerHitbox);

	int getShooterAmount();
	ShootingEnemy* getEnemyAtVectorPos(int pos);
};

#endif // ENEMYMAN_HEADER