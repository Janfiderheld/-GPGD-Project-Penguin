#include <MovingObject.h>

/// <summary>
/// Facade to manage the access to the level for all moving objects
/// </summary>
GridFacade* MovingObject::LevelFacade = nullptr;

/// <summary>
/// Constructor which sets the texture, position and bounding box to the given values
/// </summary>
/// <param name="pos">starting position for the object</param>
/// <param name="texture">texture for the object</param>
/// <param name="boundBox">bounding box (= hitbox) for the object</param>
MovingObject::MovingObject(glm::vec3 pos, Texture texture, AABB boundBox) : _texture(texture), _hitbox(boundBox) {
	position = pos;	
}

/// <summary>
/// Updates the bool values which indicate the surrounding walls. 
/// Also calculates the new position based on the current speed and clamping if jumping at a tile from below.
/// </summary>
/// <param name="deltaTime">Time since last frame to normalize calculation</param>
void MovingObject::Update(float deltaTime) {
	wasOnGround = isOnGround;
	position += speed * deltaTime;
	_hitbox.setOrigin(position);

	int flooredPosX = floor(position.x);
	int flooredPosY = floor(position.y);
	int roundPosX = round(position.x);
	int roundPosY = round(position.y);
	int ceilPosX = ceil(position.x);
	int ceilPosY = ceil(position.y);

	bool twoBottoms = LevelFacade->checkForTwoTilesInX(flooredPosX, ceilPosY - 1, _hitbox);
	bool twoCeilings = LevelFacade->checkForTwoTilesInX(flooredPosX, flooredPosY + 2, _hitbox);
	bool twoRight = LevelFacade->checkForTwoTilesInY(flooredPosX + 1, flooredPosY, _hitbox);
	bool twoLeft = LevelFacade->checkForTwoTilesInY(ceilPosX - 1, flooredPosY, _hitbox);

	bool bottomTileLeft = LevelFacade->checkForWall(flooredPosX, ceilPosY - 1);
	bool bottomTileRight = LevelFacade->checkForWall(ceilPosX, ceilPosY - 1);
	bool upperTileLeft = LevelFacade->checkForWall(flooredPosX, flooredPosY + 2);
	bool upperTileRight = LevelFacade->checkForWall(ceilPosX, flooredPosY + 2);

	bool leftWallLower = LevelFacade->checkForWall(ceilPosX - 1, flooredPosY);
	bool leftWallUpper = LevelFacade->checkForWall(ceilPosX - 1, ceilPosY);
	bool rightWallLower = LevelFacade->checkForWall(flooredPosX + 1, flooredPosY);
	bool rightWallUpper = LevelFacade->checkForWall(flooredPosX + 1, ceilPosY);

	bool clampUpperLeft = LevelFacade->checkForWall(flooredPosX, flooredPosY + 1);
	bool clampUpperRight = LevelFacade->checkForWall(ceilPosX, flooredPosY + 1);
	bool clampJump = false;

	if (twoBottoms) {
		isOnGround = bottomTileLeft || bottomTileRight;
	} else {
		isOnGround = roundPosX == ceilPosX ? bottomTileRight : bottomTileLeft;
	}

	if (twoRight) {
		hasTileRight = rightWallUpper || rightWallLower;
	} else {
		hasTileRight = roundPosY == ceilPosY ? rightWallUpper : rightWallLower;
	}

	if (twoLeft) {
		hasTileLeft = leftWallUpper || leftWallLower;
	} else {
		hasTileLeft = roundPosY == ceilPosY ? leftWallUpper : leftWallLower;
	}

	if (twoCeilings) {
		hasCeiling = upperTileLeft || upperTileRight;
		clampJump = clampUpperLeft || clampUpperRight;
	} else {
		hasCeiling = roundPosX == ceilPosX ? upperTileRight : upperTileLeft;
		clampJump = roundPosX == ceilPosX ? clampUpperRight : clampUpperLeft;
	}

	if (clampJump) {
		position.y = glm::min(position.y, (float)(flooredPosY + 1));
		speed.y = glm::min(speed.y, 0.0f);
	}
}

/// <summary>
/// Returns the hitbox of the object as a bounding box.
/// </summary>
AABB MovingObject::getHitbox() {
	return _hitbox;
}

/// <summary>
/// Returns the texture of the object.
/// </summary>
Texture MovingObject::getTexture() {
	return _texture;
}

/// <summary>
/// Returns the current position of the object.
/// </summary>
glm::vec3 MovingObject::getPosition() {
	return position;
}

/// <summary>
/// Returns the current Status of the object.
/// </summary>
MovingObjectStatus MovingObject::getCurrentStatus() {
	return status;
}