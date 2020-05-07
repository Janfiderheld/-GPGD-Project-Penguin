#include "Camera.h"

void Camera::updateVectors()
{
	//_direction = glm::normalize(_position - _target);
	_right = glm::normalize(glm::cross(_worldUp, _front));
	_up = glm::normalize(glm::cross(_front, _right));
}

Camera::Camera(glm::vec3 position, glm::vec3 worldUp)
{
	_position = position;
	_worldUp = worldUp;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	updateVectors();
}

glm::vec3 Camera::getPosition()
{
	return _position;
}

glm::vec3 Camera::getFrontVector()
{
	return _front;
}

glm::vec3 Camera::getUpVector()
{
	return _up;
}

glm::vec3 Camera::getRightVector()
{
	return _right;
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(_position, _position + _front, _up);
}

void Camera::changePosition(glm::vec3 newPos)
{
	_position = newPos;
	updateVectors();
}

void Camera::changeWorldUp(glm::vec3 newWorldUp)
{
	_worldUp = newWorldUp;
	updateVectors();
}

void Camera::processKeyboardInput(MovementDirection dir, float deltaTime)
{
	float velocity = speed * deltaTime;

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
}