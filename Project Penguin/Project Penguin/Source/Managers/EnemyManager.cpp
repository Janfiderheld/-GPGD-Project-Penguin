#include <Managers/EnemyManager.h>

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
	for(int i = 0; i < _shooters.size(); i++) {
		_shooters.at(i).calculateSpeed(delta);
		_shooters.at(i).shootProjectile(PlayerChar->getPosition());
	}
}

/// <summary>
/// Generates a set amount of enemies at random positions inside the level.
/// The amount is set as the remaining amount of specials needed in the level
/// </summary>
void EnemyManager::generateEnemies() {
	_shooters.clear();
	int size = UserInterface::MaxSpecialAmount - LevelFacade->getNumberOfSpecials();
	_shooters.resize(size);
	std::vector<int> positions;
	
	for (int i = 0; i < _shooters.size(); i++) {
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
		} while (!isUsableX);
		positions.push_back(x);
		positions.push_back(x - 1);
		positions.push_back(x - 2);
		positions.push_back(x + 1);
		positions.push_back(x + 2);
		glm::vec3 pos(x, LevelFacade->getHeightForXPos(x), -10.0f);
		_shooters.at(i) = ShootingEnemy(pos, AABB(pos, 1.0f));
	}
}

/// <summary>
///  Checks for collision with the player
/// </summary>
void EnemyManager::checkForCollision() {
}

/// <summary>
/// Returns the number of shooting enemies currently managed
/// </summary>
int EnemyManager::getShooterAndProjectileAmount() {
	return _shooters.size();
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
/// Returns a reference to the projectile at the given position in the vector
/// </summary>
Projectile* EnemyManager::getProjectileAtVectorPos(int pos) {
	if (pos < 0 || pos >= getShooterAndProjectileAmount()) {
		return nullptr;
	}

	return _shooters.at(pos).getCurrentProjectile();
}