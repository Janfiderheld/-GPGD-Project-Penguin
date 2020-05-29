#include "Camera.h"

// updates the dependant vectors 
void Camera::updateVectors()
{
	//_direction = glm::normalize(_position - _target);
	glm::vec3 right = glm::normalize(glm::cross(_worldUp, _front));
	_up = glm::normalize(glm::cross(_front, right));
}

// constructor, which sets the position & worldUp
Camera::Camera(glm::vec3 position, glm::vec3 worldUp, Character* character) {
	_position = position;
	_worldUp = worldUp;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	updateVectors();

	_target = character;
}

// returns the camera position
glm::vec3 Camera::getPosition()
{
	return _position;
}

// returns the front vector
glm::vec3 Camera::getFrontVector()
{
	return _front;
}

// returns the up vector
glm::vec3 Camera::getUpVector()
{
	return _up;
}

// calculates the view Matrix for this camera object
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(_position, _position + _front, _up);
}

// changes Position of this camera object
void Camera::changePosition(glm::vec3 newPos)
{
	_position = newPos;
	updateVectors();
}

// changes the worldUp Vector
void Camera::changeWorldUp(glm::vec3 newWorldUp)
{
	_worldUp = newWorldUp;
	updateVectors();
}

void Camera::updatePosition(float deltaTime) {
	glm::vec3 speed = _target->getCurrentSpeed();
	changePosition(getPosition() + speed * deltaTime);
}