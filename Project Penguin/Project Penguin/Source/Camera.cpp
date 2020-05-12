#include "Camera.h"

// updates the dependant vectors 
void Camera::updateVectors()
{
	//_direction = glm::normalize(_position - _target);
	_right = glm::normalize(glm::cross(_worldUp, _front));
	_up = glm::normalize(glm::cross(_front, _right));
}

// constructor, which sets the position & worldUp
Camera::Camera(glm::vec3 position, glm::vec3 worldUp)
{
	_position = position;
	_worldUp = worldUp;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	setSpeed(2.5f);
	updateVectors();
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

// returns the right vector
glm::vec3 Camera::getRightVector()
{
	return _right;
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

// processes the Keyboard Input for a given direction by repositioning the camera 
void Camera::calculatePosition(MovementDirection dir, float deltaTime)
{
	float velocity = getSpeed() * deltaTime;

	switch (dir)
	{
	case LEFT:
		_position -= _right * velocity;
		break;
	case RIGHT:
		_position += _right * velocity;
		break;
	case UP:
		_position -= _up * velocity;
		break;
	case DOWN:
		_position += _up * velocity;
		break;
	default:
		break;
	}

	updateVectors();
}