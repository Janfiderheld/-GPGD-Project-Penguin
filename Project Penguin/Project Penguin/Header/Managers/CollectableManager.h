#ifndef COLLMAN_HEADER
#define COLLMAN_HEADER

#include <Gameplay/Collectable.h>
#include <Managers/GridFacade.h>
#include <Managers/HighscoreManager.h> 
#include <vector>
#include <random>

class CollectableManager {
private:
	static int MaxCollectAmount;
	static int MinCollectAmount;
	
	std::vector<Collectable> _collectables;

public:
	static GridFacade* LevelFacade;
	static HighscoreManager* HighscoreManager;
	
	CollectableManager();

	void generateCollectables();
	void checkForCollision(AABB playerHitbox, float barrierPos);
	int getAmountOfCollectables();
	Collectable* getCollectableAtPosition(int pos);
};

#endif // COLLMAN_HEADER