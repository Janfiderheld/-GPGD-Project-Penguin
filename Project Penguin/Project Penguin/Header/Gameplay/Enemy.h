#ifndef ENEMY_HEADER
#define ENEMY_HEADER

#include <Gameplay/MovingObject.h>

class Enemy : public MovingObject {
protected:
	static float JumpSpeed;
	static float WalkSpeed;
	static float SideSpeedAir;

	static int StandCountMin;
	static int StandCountMax;
	static int StandCountError;

	static int MovementRadius;
	static float FrustumCullingRadius;

	int _standCounterMax = 0;
	int _standCounter = 0;
	int _errorCounter = 0;
	
	bool _beforePit = false;
	bool _reachedStart = false;
	bool _reachedEnd = false;

	MovingObjectStatus _lastDir = WALK_LEFT;
	float _posLastFrame;

public:
	Enemy(glm::vec3 pos, AABB boundBox);

	void calculateSpeed(float deltaTime) override;	
	bool checkWithCameraArea(glm::mat4 view, glm::mat4 proj);
	bool checkLastDirectionLeft();
};

#endif // ENEMY_HEADER 