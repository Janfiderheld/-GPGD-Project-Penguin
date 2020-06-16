#ifndef COLLECTABLE_HEADER
#define COLLECTABLE_HEADER

#include <GLM/glm.hpp>
#include <Technicals/AABB.h>
#include <Technicals/Texture.h>
#include <Technicals/DrawableVertices.h>

class Collectable : public DrawableVertices{
private:
	static int ScoreValue;
	static glm::vec3 Scale;
	static glm::vec2 TextureOffset;
	
	AABB _hitbox;
	glm::vec3 _position;

	bool _isCollected = false;

public:
	static Texture* CollectTex;
	
	Collectable();
	Collectable(glm::vec2 pos);

	AABB getHitbox();
	glm::vec3 getPosition();
	glm::vec3 getScale();
	int getScore();

	bool isCollected();
	void collect();
};

#endif // COLLECTABLE_HEADER