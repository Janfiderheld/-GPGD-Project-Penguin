#ifndef THEME_CHANGER_HEADER
#define THEME_CHANGER_HEADER

#include <IResetable.h>
#include <ILighting.h>
#include <GLM/glm.hpp>
#include <Gameplay/Character.h>

class ThemeChangingManager : public IResetable, public ILighting {
private:
	const float MovementSpeed = 0.85f;
	
	glm::vec3 _position;

public:
	static int PointsPerTile;
	static Character* PlayerChar;
	
	ThemeChangingManager(glm::vec3 pos);

	void updatePosition(float deltaTime);
	void checkForPlayerCollision();
	void reset() override;

	float getCurrentX();
	glm::vec3 getPosition();
};

#endif // THEME_CHANGER_HEADER