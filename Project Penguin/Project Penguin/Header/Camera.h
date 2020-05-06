#ifndef CAMERA_HEADER
#define CAMERA_HEADER

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

enum MovementDirection {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
private:
	glm::vec3 _position;
	glm::vec3 _front;
	glm::vec3 _right;
	glm::vec3 _up;
	glm::vec3 _worldUp;

	const float speed = 2.5f;

	void updateVectors();

public:
	Camera(glm::vec3 position, glm::vec3 worldUp);

	glm::vec3 getPosition();
	glm::vec3 getDirection();

	glm::mat4 getViewMatrix();

	void changePosition(glm::vec3 newPos);
	void changeWorldUp(glm::vec3 newWorldUp);

	void processKeyboardInput(MovementDirection dir, float deltaTime);
};

#endif // CAMERA_HEADER