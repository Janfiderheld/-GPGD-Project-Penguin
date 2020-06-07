#ifndef COLLMAN_HEADER
#define COLLMAN_HEADER

#include <Gameplay/Collectable.h>
#include <Managers/GridFacade.h>
#include <Managers/HighscoreManager.h> 
#include <vector>
#include <random>

class CollectableManager {
private:
	const int MaxCollectAmount = 12;
	const int MinCollectAmount = 6;
	
	std::vector<Collectable> _collectables;

	void generateCollectables();
public:
	static GridFacade* LevelFacade;
	static HighscoreManager* HighscoreMan;
	
	CollectableManager();

	std::vector<Collectable>* getCollectables();
	void checkForCollection(AABB playerHitbox);
};

#endif // COLLMAN_HEADER