#ifndef COLLMAN_HEADER
#define COLLMAN_HEADER

#include <Gameplay/Collectable.h>
#include <Managers/GridFacade.h>
#include <vector>
#include <random>

class CollectableManager {
private:
	const int MaxCollectAmount = 20;
	const int MinCollectAmount = 10;
	
	std::vector<Collectable> _collectables;

	void generateCollectables();
public:
	static GridFacade* LevelFacade;
	
	CollectableManager();
};

#endif // COLLMAN_HEADER