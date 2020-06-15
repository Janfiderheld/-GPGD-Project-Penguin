#ifndef PROJECTILE_HEADER
#define PROJECTILE_HEADER

#include <Gameplay/MovingObject.h>
#include <Technicals/Texture.h>
#include <Technicals/DrawableVertices.h>

class Projectile : public MovingObject, public DrawableVertices {
private:
	static int MaxDistanceBeforeDestroy;
	static float Speed;

	MovingObjectStatus _movDir = WALK_LEFT;
	bool _isActive = false;
	
public:
	static Texture* ProjectileTex;
	static glm::vec3 Scale;
	
	Projectile();
	Projectile(glm::vec3 pos, AABB boundBox, MovingObjectStatus dir);

	void calculateSpeed(float deltaTime) override;
	void shouldDeactivate();
	
	static Texture* getTexture();
	bool getStatus();	
	
	void changeStatus(bool state);
	void setPosition(glm::vec3 newPos);
	void changeDirection(MovingObjectStatus dir);
};

#endif // PROJECTILE_HEADER