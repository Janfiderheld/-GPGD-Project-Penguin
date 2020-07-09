#include <Managers/EnemyManager.h>

/// <summary>
/// Amount of specials for each level.
/// Specials include enemies, pits & platforms
/// </summary>
int EnemyManager::MaxSpecialAmount = 12;

/// <summary>
/// Counts towards this value between two possible collisions
/// </summary>
int EnemyManager::MaxCollisionDowntime = 45;

/// <summary>
/// Points for killing a shooting enemy
/// </summary>
int EnemyManager::ShooterPoints = 25;

/// <summary>
/// Probability (in %) to spawn a shooting enemy
/// </summary>
int EnemyManager::ShooterProb = 60;

/// <summary>
/// Facade to manage the access to the level for all placing the collectables
/// </summary>
GridFacade* EnemyManager::LevelFacade = nullptr;

/// <summary>
/// Reference to the player character
/// </summary>
Character* EnemyManager::PlayerChar = nullptr;

/// <summary>
/// Reference to the HighscoreManager
/// </summary>
HighscoreManager* EnemyManager::HighscoreManager = nullptr;

/// <summary>
/// Generates the enemies and sets the seed for the randomizer
/// </summary>
EnemyManager::EnemyManager() {
	srand(time(NULL));
	generateEnemies();
}

/// <summary>
/// Updates the position of all enemies & projectiles each frame
/// </summary>
/// <param name="delta">time since last frame</param>
void EnemyManager::updateEnemies(float delta, float barrierPos, glm::mat4 view, glm::mat4 proj) {
	if (_collCounter <= MaxCollisionDowntime) {
		_collCounter++;
	}
	
	for(int i = 0; i < _shooters.size(); i++) {
		if(_shooters.at(i).checkWithCameraArea(view, proj))	{
			if(!checkForCollisionWithPlayer(i, SHOOTER))	{
				if(!checkForCollisionWithBarrier(i, SHOOTER, barrierPos)) {
					_shooters.at(i).calculateSpeed(delta);
				} else {
					continue;
				}
			} else {
				continue;
			}
		}
		
		if(_shooters.at(i).getCurrentProjectile()->checkWithCameraArea(view, proj)) {
			if(!checkForCollisionWithPlayer(i, PROJECTILE))	{
				if(!checkForCollisionWithBarrier(i, PROJECTILE, barrierPos)) {
					_shooters.at(i).shootProjectile(PlayerChar->getPosition());
				} else {
					continue;
				}
			} else {
				continue;
			}
		}
	}
	
	for (int i = 0; i < _walkers.size(); i++) {
		if(_walkers.at(i).checkWithCameraArea(view, proj)) {
			if (!checkForCollisionWithPlayer(i, WALKER)) {
				if (!checkForCollisionWithBarrier(i, WALKER, barrierPos)) {
					_walkers.at(i).calculateSpeed(delta);
				} else {
					continue;
				}
			} else {
				continue;
			}
		}
	}
}

/// <summary>
/// Generates a set amount of enemies at random positions inside the level.
/// The amount is set as the remaining amount of specials needed in the level
/// </summary>
void EnemyManager::generateEnemies() {
	_shooters.clear();
	_walkers.clear();
	int enemAmount = MaxSpecialAmount - LevelFacade->getNumberOfSpecials();
	std::vector<int> positions;
	
	for (int i = 0; i < enemAmount; i++) {
		bool isUsableX = false;
		int x = 0;
		do {
			x = LevelFacade->generateRandomForPlacement();

			isUsableX = true;
			for (int j = 0; j < positions.size(); j++) {
				if (positions.at(j) == x) {
					isUsableX = false;
					break;
				}
			}
			if(LevelFacade->getHeightForXPos(x) == 0) {
				isUsableX = false;
				positions.push_back(x);
			}
			if (LevelFacade->getHeightForXPos(x - 1) == 0 && LevelFacade->getHeightForXPos(x + 1) == 0) {
				isUsableX = false;
				positions.push_back(x);
			}
		} while (!isUsableX);
		
		positions.push_back(x);
		positions.push_back(x - 1);
		positions.push_back(x - 2);
		positions.push_back(x + 1);
		positions.push_back(x + 2);

		glm::vec3 pos(x, LevelFacade->getHeightForXPos(x), -10.0f);
		if(rand() % 100 <= ShooterProb)	{
			_shooters.emplace_back(pos, AABB(pos, ShootingEnemy::getScale().y, ShootingEnemy::getScale().x));
		} else {
			_walkers.emplace_back(pos, AABB(pos, WalkingEnemy::getScale().y, WalkingEnemy::getScale().x));
		}
	}
}

/// <summary>
///  Checks if the player collides with either an enemy or a projectile
/// </summary>
bool EnemyManager::checkForCollisionWithPlayer(int index, EnemyType type) {
	if (_collCounter <= MaxCollisionDowntime) {
		return false;
	}

	switch (type)
	{
	case SHOOTER: {
			ShootingEnemy* shooter = getShootingEnemyAtVectorPos(index);
			bool hurtfulColl = PlayerChar->getHitbox().checkCollision(shooter->getHitbox());
			bool killingColl = PlayerChar->getHitbox().checkCollision(*shooter->getKillBox());

			if (hurtfulColl || killingColl) {
				if (!killingColl) {
					PlayerChar->looseHealth();
					_collCounter = 0;
				}
				if (killingColl) {
					HighscoreManager->addToCurrentScore(ShooterPoints);
				}
				_shooters.erase(_shooters.begin() + index);
				return true;
			}

		}
		
		break;
	
	case WALKER: {
			WalkingEnemy* walker = getWalkingEnemyAtVectorPos(index);
			if (PlayerChar->getHitbox().checkCollision(walker->getHitbox())) {
				PlayerChar->looseHealth();
				_walkers.erase(_walkers.begin() + index);
				_collCounter = 0;
				return true;
			}
		}
		
		break;

	case PROJECTILE: {
			Projectile* proj = _shooters.at(index).getCurrentProjectile();
			if (!proj->getStatus()) {
				return false;
			}

			if (PlayerChar->getHitbox().checkCollision(proj->getHitbox())) {
				PlayerChar->looseHealth();
				proj->changeStatus(false);
				_collCounter = 0;
				return true;
			}
		}
		
		break;
	}

	return false;
}

/// <summary>
/// Checks if an enemy collides with the level changing barrier and kills the enemy accordingly
/// </summary>
bool EnemyManager::checkForCollisionWithBarrier(int index, EnemyType type, float barrierPos) {
	switch (type)
	{
	case SHOOTER: {
			ShootingEnemy* shooter = getShootingEnemyAtVectorPos(index);
			if (shooter->getPosition().x < barrierPos) {
				shooter->getCurrentProjectile()->changeStatus(false);
				_shooters.erase(_shooters.begin() + index);
				return true;
			}
		}

		break;

	case WALKER: {
			WalkingEnemy* walker = getWalkingEnemyAtVectorPos(index);
			if (walker->getPosition().x < barrierPos) {
				_walkers.erase(_walkers.begin() + index);
				return true;
			}
		}
		
		break;

	case PROJECTILE: {
			Projectile* proj = _shooters.at(index).getCurrentProjectile();
			if (proj->getStatus()) {
				if (proj->getPosition().x < barrierPos) {
					proj->changeStatus(false);
					return true;
				}
			}
		}
		
		break;
	}

	return false;
}

/// <summary>
/// Returns the number of shooting enemies currently managed
/// </summary>
int EnemyManager::getShooterAndProjectileAmount() {
	return _shooters.size();
}

/// <summary>
/// Returns the number of walking enemies currently managed
/// </summary>
int EnemyManager::getWalkerAmount() {
	return _walkers.size();
}

/// <summary>
/// Returns a reference to the shooting enemy at the given position in the vector
/// </summary>
ShootingEnemy* EnemyManager::getShootingEnemyAtVectorPos(int pos) {
	if (pos < 0 || pos >= getShooterAndProjectileAmount()) {
		return nullptr;
	}

	return &_shooters.at(pos);
}

/// <summary>
/// Returns a reference to the walking enemy at the given position in the vector
/// </summary>
WalkingEnemy* EnemyManager::getWalkingEnemyAtVectorPos(int pos) {
	if (pos < 0 || pos >= getWalkerAmount()) {
		return nullptr;
	}

	return &_walkers.at(pos);
}

/// <summary>
/// Returns a reference to the projectile at the given position in the vector
/// </summary>
Projectile* EnemyManager::getProjectileAtVectorPos(int pos) {
	if (pos < 0 || pos >= getShooterAndProjectileAmount()) {
		return nullptr;
	}

	return _shooters.at(pos).getCurrentProjectile();
}