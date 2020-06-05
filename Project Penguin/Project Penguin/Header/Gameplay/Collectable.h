#ifndef COLLECTABLE_HEADER
#define COLLECTABLE_HEADER

#include <GLM/glm.hpp>
#include <Technicals/AABB.h>
#include <Technicals/Texture.h>
#include <Technicals/DrawableVertices.h>

class Collectable : public DrawableVertices{
private:
	const int ScoreValue = 10;
	const glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	
	AABB _hitbox;
	glm::vec3 _position;

	bool _isCollected = false;

public:
	static Texture CollectTex;
	
	Collectable();
	Collectable(glm::vec3 pos, AABB boundBox);

	AABB getHitbox();
	glm::vec3 getPosition();
	glm::vec3 getScale();
	int getScore();

	bool isCollected();
	void collect();
};

#endif // COLLECTABLE_HEADER