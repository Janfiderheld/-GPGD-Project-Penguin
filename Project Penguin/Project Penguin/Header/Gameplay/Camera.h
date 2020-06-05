#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <Gameplay/Character.h>

class Camera {
private:
	const int CharFollowStart = 6;
	const int MaxHeight = 7;

	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _up;
	glm::vec3 _worldUp;
	
	Character* _target;

	void updateVectors();

public:
	Camera(glm::vec3 position, glm::vec3 worldUp, Character* character);

	glm::vec3 getPosition();
	glm::mat4 getViewMatrix();

	void changePosition(glm::vec3 newPos);
	void changeWorldUp(glm::vec3 newWorldUp);
	void updatePosition(float deltaTime);
};

#endif // CAMERA_HEADER