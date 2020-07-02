#ifndef THEME_CHANGER_HEADER
#define THEME_CHANGER_HEADER

#include <GLM/glm.hpp>
#include <Gameplay/Character.h>
#include <IResetable.h>

class ThemeChangingManager : public IResetable {
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