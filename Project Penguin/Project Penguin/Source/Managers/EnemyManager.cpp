#include <Managers/EnemyManager.h>

/// <summary>
/// Amount of specials for each level.
/// Specials include enemies, pits & platforms
/// </summary>
int EnemyManager::MaxSpecialAmount = 12;

/// <summary>
/// Facade to manage the access to the level for all placing the collectables
/// </summary>
GridFacade* EnemyManager::LevelFacade = nullptr;

/// <summary>
/// Reference to the player character
/// </summary>
Character* EnemyManager::PlayerChar = nullptr;

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
void EnemyManager::updateEnemies(float delta) {
	checkForCollision();
	
	for(int i = 0; i < _shooters.size(); i++) {
		_shooters.at(i).calculateSpeed(delta);
		_shooters.at(i).shootProjectile(PlayerChar->getPosition());
	}

	for(int i = 0; i < _walkers.size(); i++) {
		_walkers.at(i).calculateSpeed(delta);
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
void EnemyManager::checkForCollision() {
	for(int i = 0; i < _shooters.size(); i++) {
		ShootingEnemy* shooter = getShootingEnemyAtVectorPos(i);
		bool hurtfulColl = PlayerChar->getHitbox().checkCollision(shooter->getHitbox());
		bool killingColl = PlayerChar->getHitbox().checkCollision(*shooter->getKillBox());
		if (hurtfulColl || killingColl && !_currCollision) {
			if (!killingColl) {
				PlayerChar->looseHealth();
			}
			_shooters.erase(_shooters.begin() + i);
			_currCollision = true;
			return;
		} else {
			_currCollision = false;
		}

		Projectile* proj = _shooters.at(i).getCurrentProjectile();
		if (!proj->getStatus()) {
			continue;
		}

		if (PlayerChar->getHitbox().checkCollision(proj->getHitbox())) {
			if (!_currCollision) {
				PlayerChar->looseHealth();
				proj->changeStatus(false);
				_currCollision = true;
				return;
			}
		} else {
			_currCollisionProject = false;
		}
	}

	for(int i = 0; i < _walkers.size(); i++) {
		WalkingEnemy* walker = getWalkingEnemyAtVectorPos(i);
		if (PlayerChar->getHitbox().checkCollision(walker->getHitbox())) {
			if (!_currCollision) {
				PlayerChar->looseHealth();
				_walkers.erase(_walkers.begin() + i);
				_currCollision = true;
				return;
			}
		} else {
			_currCollision = false;
		}
	}
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