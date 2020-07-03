#ifndef PROJECTILE_HEADER
#define PROJECTILE_HEADER

#include <ILighting.h>
#include <Gameplay/MovingObject.h>
#include <Technicals/Texture.h>
#include <Technicals/DrawableVertices.h>

class Projectile : public MovingObject, public DrawableVertices, public ILighting {
private:
	static int MaxDistanceBeforeDestroy;
	static float Speed;
	static glm::vec2 TextureOffset;

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
	bool checkWithCameraArea(glm::mat4 view, glm::mat4 proj);
	
	void changeStatus(bool state);
	void changeDirection(MovingObjectStatus dir);
	void setPosition(glm::vec3 newPos);
	glm::vec3 getTexturePosition();
};

#endif // PROJECTILE_HEADER