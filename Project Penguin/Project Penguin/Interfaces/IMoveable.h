#ifndef MOVE_INTERACE
#define MOVE_INTERACE

#include <GLM/glm.hpp>

class IMovable {
protected:
	glm::vec3 speed;

public:
	virtual void calculateSpeed(float deltaTime) = 0;

	glm::vec3 getCurrentSpeed() {
		return speed;
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