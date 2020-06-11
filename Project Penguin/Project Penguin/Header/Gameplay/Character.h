#ifndef CHAR_HEADER
#define CHAR_HEADER

#include <Gameplay/MovingObject.h>
#include <Technicals/DrawableVertices.h>
#include <Managers/InputManager.h>
#include <Technicals/Texture.h>
#include <Technicals/AABB.h>

class Character : public MovingObject, public DrawableVertices {
private:
	const float JumpSpeed = 2.0f;
	const float WalkSpeed = 2.0f;
	const float SideSpeedAir = 1.25f;
	
	const int MaxHealth = 3;	
	int _currentHealth = MaxHealth;
	
	bool _reachedEnd = false;
	bool _rechedPitBottom = false;
	
	void checkForReachedEnd();
	void checkForPitBottom();
	
public:
	static InputManager* InputManager;

	Character(glm::vec3 pos, Texture texture, AABB boundBox);

	virtual void calculateSpeed(float deltaTime);
	
	bool hasReachedEnd();
	bool hasDied();
	void looseHealth();
	int getCurrentHealth();
	int getMaxHealth();
};

#endif // CHAR_HEADER