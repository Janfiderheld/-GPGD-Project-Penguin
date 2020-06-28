#include <Managers/CollectableManager.h>

/// <summary>
/// Maximum amount of spawned collectables
/// </summary>
int CollectableManager::MaxCollectAmount = 12;

/// <summary>
/// Minimum amount of spawned collectables
/// </summary>
int CollectableManager::MinCollectAmount = 6;

/// <summary>
/// Facade to manage the access to the level for all placing the collectables
/// </summary>
GridFacade* CollectableManager::LevelFacade = nullptr;

/// <summary>
/// Manages the highscores and the current score
/// </summary>
HighscoreManager* CollectableManager::HighscoreManager = nullptr;

/// <summary>
/// Places a random number of collectables at random points throughout the levels.
/// For each point a random x-coordinate is chosen.
/// Afterwards a random height between [0, 2) is added to the highest y-coordinate at that point.
/// This position is then used for a collectable, if it is not inside of a platform tile.
/// </summary>
void CollectableManager::generateCollectables() {
	_collectables.clear();
	int size = rand() % (MaxCollectAmount - MinCollectAmount) + MinCollectAmount;
	_collectables.resize(size);	
	std::vector<glm::vec2>* positions = LevelFacade->getCollectablePositions();
	int noOfPlatformCollectables = positions->size();
	for (int i = 0; i < noOfPlatformCollectables; i++) {
		_collectables.at(i) = Collectable(positions->at(i));
	}

	for (int i = 0; i < _collectables.size() - noOfPlatformCollectables; i++) {
		bool isUsableX = false;
		int x = 0, y = 0, height = 0;
		do {
			x = LevelFacade->generateRandomForPlacement();

			isUsableX = true;
			for (int j = 0; j < positions->size(); j++) {
				if (positions->at(j).x == x) {
					isUsableX = false;
					break;
				}
			}

			y = LevelFacade->getHeightForXPos(x);
			height = rand() % 3;
			if (y == 0 || LevelFacade->checkForWall(x, y + height)) {
				isUsableX = false;
			}
		} while (!isUsableX);
		y += height;
		positions->push_back(glm::vec2(x, y));
		_collectables.at(i + noOfPlatformCollectables) = Collectable(glm::vec2(x, y));
	}
}

/// <summary>
/// Creates the collectable Manager by setting the random seed, calculating the amount of collectables and generating them.
/// </summary>
CollectableManager::CollectableManager() {
	srand(time(NULL));
	generateCollectables();
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
			HighscoreManager->addToCurrentScore(temp->getScore());
		}
	}
}

/// <summary>
/// Number of collectables currently managed
/// </summary>
int CollectableManager::getAmountOfCollectables() {
	return _collectables.size();
}

/// <summary>
/// Returns the collectable at the given position
/// </summary>
Collectable* CollectableManager::getCollectableAtPosition(int pos) {
	if (pos < 0 || pos >= getAmountOfCollectables()) {
		return nullptr;
	}

	return &_collectables.at(pos);
}