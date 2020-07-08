#ifndef CHAR_HEADER
#define CHAR_HEADER

#include <Gameplay/MovingObject.h>
#include <Managers/InputManager.h>
#include <Technicals/DrawableVertices.h>
#include <Technicals/Texture.h>
#include <Technicals/AABB.h>

class Character : public MovingObject, public DrawableVertices {
private:
	static glm::vec3 Scale;
	static glm::vec2 TextureOffset;
	
	static float JumpSpeed;
	static float WalkSpeed;
	static float SideSpeedAir;
	
	static int MaxHealth;
	int _currentHealth = MaxHealth;
	
	bool _reachedEnd = false;
	bool _reachedPitBottom = false;
	bool _atLeftLevelEnd = false;
	bool _atRightLevelEnd = false;

	MovingObjectStatus _lastDir = WALK_RIGHT;
	Texture* _tex;
	
	void checkForPitBottom();
	
public:
	static int PointsPerHeart;
	static InputManager* InputManager;
	static glm::vec3 getScale();

	Character(glm::vec3 pos, Texture* texture, AABB boundBox);

	void calculateSpeed(float deltaTime) override;
	void reset() override;
	
	bool hasReachedEnd();
	bool checkLastDirectionLeft();

	bool hasDied();
	void looseHealth();
	void dieInstantly();
	
	int getCurrentHealth();
	int getMaxHealth();
	Texture* getTexture();
	glm::vec3 getTexturePosition();
};

#endif // CHAR_HEADER