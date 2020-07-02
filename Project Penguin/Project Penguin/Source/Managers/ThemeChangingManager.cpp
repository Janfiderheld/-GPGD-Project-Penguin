#include <Managers/ThemeChangingManager.h>

/// <summary>
/// Points the Player gets for every tile between them and the theme barrier when the end is reached
/// </summary>
int ThemeChangingManager::PointsPerTile = 5;

/// <summary>
/// Main Character to check for collision
/// </summary>
Character* ThemeChangingManager::PlayerChar = nullptr;

/// <summary>
/// Sets the starting position based on the parameter
/// </summary>
ThemeChangingManager::ThemeChangingManager(glm::vec3 pos) {
	startPos = pos;
	_position = pos;
}

/// <summary>
/// Updates the position every frame based on the delta time to move the theme changing barrier forward.
/// Also checks for a possible collision with the player
/// </summary>
/// <param name="deltaTime">time since last frame</param>
void ThemeChangingManager::updatePosition(float deltaTime) {
	_position.x += deltaTime * MovementSpeed;
	checkForPlayerCollision();
}

/// <summary>
/// Checks if the player has overlapped with the barrier
/// </summary>
void ThemeChangingManager::checkForPlayerCollision() {
	if(PlayerChar->getPosition().x < _position.x) {
		PlayerChar->dieInstantly();
	}
}

/// <summary>
/// Resets the level theme after a game has finished
/// </summary>
void ThemeChangingManager::reset() {
	_position = startPos;
}

/// <summary>
/// Returns the current position on the x-axis of the barrier
/// </summary>
/// <returns></returns>
float ThemeChangingManager::getCurrentX() {
	return _position.x;
}

/// <summary>
/// Returns the current position
/// </summary>
glm::vec3 ThemeChangingManager::getPosition() {
	return _position;
}