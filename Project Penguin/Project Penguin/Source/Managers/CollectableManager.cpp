#include <Managers/CollectableManager.h>

/// <summary>
/// Facade to manage the access to the level for all placing the collectables
/// </summary>
GridFacade* CollectableManager::LevelFacade = nullptr;

/// <summary>
/// 
/// </summary>
void CollectableManager::generateCollectables() {
	std::vector<glm::vec2>* positions = LevelFacade->getCollectablePositions();
	int noOfPlatformCollectables = positions->size();
	for (int i = 0; i < noOfPlatformCollectables; i++) {
		_collectables.at(i) = Collectable(positions->at(i));
	}

	for (int i = 0; i < _collectables.size() - noOfPlatformCollectables; i++) {
		bool isUsableX = false;
		int x = 0;
		do {
			x = LevelFacade->generateRandomForPlacement();

			isUsableX = true;
			for (int j = 0; j < positions->size(); j++) {
				if (positions->at(j).x == x) {
					isUsableX = false;
					break;
				}
			}

			if (LevelFacade->getHeightForXPos(x) == 0) {
				isUsableX = false;
			}
		} while (!isUsableX);
		int y = LevelFacade->getHeightForXPos(x);
		positions->push_back(glm::vec2(x, y));
		int height = rand() % 3;
		_collectables.at(i + noOfPlatformCollectables) = Collectable(glm::vec2(x, y + height));
	}
}

/// <summary>
/// 
/// </summary>
CollectableManager::CollectableManager() {
	srand(time(NULL));
	int size = rand() % (MaxCollectAmount - MinCollectAmount) + MinCollectAmount;
	_collectables.resize(size);
	generateCollectables();
}

/// <summary>
/// Returns a reference to the vector containing all collectables
/// </summary>
std::vector<Collectable>* CollectableManager::getCollectables() {
	return &_collectables;
}

/// <summary>
/// Checks if the player character collides with one of the collectables.
/// If a collision is found, that collectable is marked and deleted.
/// </summary>
/// <param name="playerHitbox">Hitbox of the player to check against</param>
void CollectableManager::checkForCollection(AABB playerHitbox) {
	for (int i = 0; i < _collectables.size(); i++) {
		Collectable* temp = &_collectables.at(i);
		if (playerHitbox.checkCollision(temp->getHitbox())) {
			temp->collect();
			_collectables.erase(_collectables.begin() + i);
		}
	}
}