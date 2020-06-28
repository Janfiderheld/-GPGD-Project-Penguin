#ifndef ENEMYMAN_HEADER
#define ENEMYMAN_HEADER

#include <vector>
#include <random>
#include <Gameplay/ShootingEnemy.h>
#include <Gameplay/WalkingEnemy.h>
#include <Gameplay/Projectile.h>
#include <Gameplay/Character.h>
#include <Managers/GridFacade.h>
#include <Managers/HighscoreManager.h>
#include <Managers/ThemeChangingManager.h>
#include <Technicals/AABB.h>

class EnemyManager {
private:
	static int MaxSpecialAmount;
	static int MaxCollisionDowntime;
	static int ShooterPoints;
	static int ShooterProb;

	std::vector<ShootingEnemy> _shooters;
	std::vector<WalkingEnemy> _walkers;

	int _collCounter = 0;

public: 
	static GridFacade* LevelFacade;
	static Character* PlayerChar;
	static HighscoreManager* HighscoreManager;
	static ThemeChangingManager* ThemeChanger;

	EnemyManager();

	void updateEnemies(float delta);	
	void generateEnemies();
	void checkForCollisionWithPlayer();
	void checkForCollisionWithBarrier();

	int getShooterAndProjectileAmount();
	int getWalkerAmount();
	ShootingEnemy* getShootingEnemyAtVectorPos(int pos);
	WalkingEnemy* getWalkingEnemyAtVectorPos(int pos);
	Projectile* getProjectileAtVectorPos(int pos);
};

#endif // ENEMYMAN_HEADER