#ifndef WALKENEMY_HEADER
#define WALKENEMY_HEADER

#include <Gameplay/Enemy.h>
#include <Technicals/Texture.h>

class WalkingEnemy : public Enemy, public DrawableVertices {
private:
	static glm::vec3 Scale;
	static glm::vec2 TextureOffset;
		
public:
	static Texture* WalkerTex;
	static glm::vec3 getScale();

	WalkingEnemy();
	WalkingEnemy(glm::vec3 pos, AABB boundBox);

	glm::vec3 getTexturePosition() override;
	void updateBoundaries(float deltaTime) override;
};

#endif // WALKENEMY_HEADER