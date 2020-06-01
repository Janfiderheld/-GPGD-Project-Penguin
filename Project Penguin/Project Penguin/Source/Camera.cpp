#include "Camera.h"

/// <summary>
/// Sets the camera position, the world up and a reference to the player character.
/// Calculates the dependent values based on these inputs.
/// </summary>
/// <param name="position">starting position of the camera</param>
/// <param name="worldUp">vector pointing up in the world</param>
/// <param name="character">reference to player character</param>
Camera::Camera(glm::vec3 position, glm::vec3 worldUp, Character* character) {
	_position = position;
	_worldUp = worldUp;
	_front = glm::vec3(0.0f, 0.0f, -1.0f);
	updateVectors();

	_target = character;
}

/// <summary>
/// Calculates the dependant vectors (camera right & camera up) based on the private values.
/// </summary>
void Camera::updateVectors() {
	glm::vec3 right = glm::normalize(glm::cross(_worldUp, _front));
	_up = glm::normalize(glm::cross(_front, right));
}

/// <summary>
/// Returns the current position of the camera.
/// </summary>
/// <returns></returns>
glm::vec3 Camera::getPosition() {
	return _position;
}

/// <summary>
/// Returns the view-Matrix for the camera based on the camera values.
/// </summary>
glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(_position, _position + _front, _up);
}

/// <summary>
/// Set position of the camera to the given value.
/// </summary>
void Camera::changePosition(glm::vec3 newPos) {
	_position = newPos;
}

/// <summary>
/// Set direction of world up to the given value and update the dependant values.
/// </summary>
void Camera::changeWorldUp(glm::vec3 newWorldUp) {
	_worldUp = newWorldUp;
	updateVectors();
}

/// <summary>
/// Update the camera position to work in sync with the player characters movement.
/// </summary>
/// <param name="deltaTime">passed time since last frame update</param>
void Camera::updatePosition(float deltaTime) {
	if (_target->getPosition().x < CharFollowStart) {
		return;
	}

	glm::vec3 speed = _target->getCurrentSpeed();
	if (speed.y != 0.0f && _target->getPosition().y <= MaxHeight) {
		speed.y = 0.0f;
	}
	changePosition(getPosition() + speed * deltaTime);
}