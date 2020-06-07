#include <Gameplay/MovingObject.h>

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

	int floorPosX = floor(position.x);
	int floorPosY = floor(position.y);
	int roundPosX = round(position.x);
	int roundPosY = round(position.y);
	int ceilPosX = ceil(position.x);
	int ceilPosY = ceil(position.y);

	bool twoInXDir = LevelFacade->checkForTwoTiles(position.x, _hitbox.getWidth());
	bool twoInYDir = LevelFacade->checkForTwoTiles(position.y, _hitbox.getHeight());

	bool bottomTileLeft = LevelFacade->checkForWall(floorPosX, ceilPosY - 1);
	bool bottomTileRight = LevelFacade->checkForWall(ceilPosX, ceilPosY - 1);
	bool upperTileLeft = LevelFacade->checkForWall(floorPosX, floorPosY + 2);
	bool upperTileRight = LevelFacade->checkForWall(ceilPosX, floorPosY + 2);

	bool leftWallLower = LevelFacade->checkForWall(ceilPosX - 1, floorPosY);
	bool leftWallUpper = LevelFacade->checkForWall(ceilPosX - 1, ceilPosY);
	bool rightWallLower = LevelFacade->checkForWall(floorPosX + 1, floorPosY);
	bool rightWallUpper = LevelFacade->checkForWall(floorPosX + 1, ceilPosY);

	bool clampUpperLeft = LevelFacade->checkForWall(floorPosX, floorPosY + 1);
	bool clampUpperRight = LevelFacade->checkForWall(ceilPosX, floorPosY + 1);
	bool clampJump = false;

	if (twoInXDir) {
		isOnGround = bottomTileLeft || bottomTileRight;
		hasCeiling = upperTileLeft || upperTileRight;
		clampJump = clampUpperLeft || clampUpperRight;
	} else {
		isOnGround = roundPosX == ceilPosX ? bottomTileRight : bottomTileLeft;
		hasCeiling = roundPosX == ceilPosX ? upperTileRight : upperTileLeft;
		clampJump = roundPosX == ceilPosX ? clampUpperRight : clampUpperLeft;
	}

	if (twoInYDir) {
		hasTileRight = rightWallUpper || rightWallLower;
		hasTileLeft = leftWallUpper || leftWallLower;
	} else {
		hasTileRight = roundPosY == ceilPosY ? rightWallUpper : rightWallLower;
		hasTileLeft = roundPosY == ceilPosY ? leftWallUpper : leftWallLower;
	}

	if (clampJump) {
		position.y = glm::min(position.y, (float)(floorPosY + 1));
		speed.y = glm::min(speed.y, 0.0f);
	}

	if(isOnGround) {
		position.y = glm::max(position.y, (float)floorPosY);
		speed.y = glm::max(speed.y, 0.0f);
	}

	position += speed * deltaTime;
	_hitbox.setOrigin(position);
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