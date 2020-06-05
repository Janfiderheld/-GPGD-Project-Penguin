#include <Managers/CollectableManager.h>

/// <summary>
/// Facade to manage the access to the level for all placing the collectables
/// </summary>
GridFacade* CollectableManager::LevelFacade = nullptr;

/// <summary>
/// 
/// </summary>
void CollectableManager::generateCollectables() {
	// TODO: Generate collectables at specific positions
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