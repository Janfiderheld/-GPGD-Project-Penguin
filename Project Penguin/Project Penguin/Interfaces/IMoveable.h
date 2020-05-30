#ifndef MOVE_INTERACE
#define MOVE_INTERACE

#include <GLM/glm.hpp>

class IMovable {
protected:
	glm::vec3 speed;
	glm::vec3 oldSpeed;

public:
	virtual void calculatePosition(float deltaTime) = 0;

	glm::vec3 getCurrentSpeed() {
		return speed;
	}

	glm::vec3 getOldSpeed() {
		return oldSpeed;
	}

	void setCompleteSpeed(glm::vec3 newSpeed) {
		speed = newSpeed;
	}

	void setVerticalSpeed(float newSpeed) {
		speed.y = newSpeed;
	}

	void setHorizontalSpeed(float newSpeed) {
		speed.x = newSpeed;
	}
};

#endif // MOVE_INTERACE