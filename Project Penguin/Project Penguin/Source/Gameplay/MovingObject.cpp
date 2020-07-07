#include <Gameplay/MovingObject.h>

/// <summary>
/// Gravity for the level which works on this object
/// </summary>
float MovingObject::Gravity = -1.0f;

/// <summary>
/// Maxmimum speed to fall with in y direction
/// </summary>
float MovingObject::MaxFallingSpeed = -2.75;

/// <summary>
/// Facade to manage the access to the level for all moving objects
/// </summary>
GridFacade* MovingObject::LevelFacade = nullptr;

/// <summary>
/// Constructor which sets the texture, position and bounding box to the given values
/// </summary>
/// <param name="pos">starting position for the object</param>
/// <param name="boundBox">bounding box (= hitbox) for the object</param>
MovingObject::MovingObject(glm::vec3 pos, AABB boundBox) : _hitbox(boundBox) {
	setCompleteSpeed(glm::vec3(0.0f));
	position = pos;
	startPos = pos;
}

/// <summary>
/// Updates the bool values which indicate the surrounding walls. 
/// Also calculates the new position based on the current speed and clamping if jumping at a tile from below.
/// </summary>
void MovingObject::updateBoundaries(float deltaTime) {
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

	updatePosition(deltaTime);
}

/// <summary>
/// Updates the objects position
/// </summary>
/// <param name="deltaTime">Time since last frame to normalize calculation</param>
void MovingObject::updatePosition(float deltaTime) {
	position += speed * deltaTime;
	_hitbox.setOrigin(position);
}

/// <summary>
/// Returns true if the object would be falling inside a pit, if it would follow in this direction
/// </summary>
bool MovingObject::checkForPit(MovingObjectStatus dir) {
	if (dir != WALK_RIGHT && dir != WALK_LEFT) {
		return false;
	}

	int x = dir == WALK_RIGHT ? ceil(position.x) : floor(position.x);
	if (LevelFacade->getHeightForXPos(x) == 0) {
		return true;
	}

	return false;
}

/// <summary>
/// Returns true if the object faces a two tile high wall
/// </summary>
/// <param name="dir">Direction the player currently faces</param>
bool MovingObject::checkForDoubleWall(MovingObjectStatus dir) {
	if (dir != WALK_LEFT && dir != WALK_RIGHT) {
		return false;
	}

	int nextY = LevelFacade->getHeightForXPos(round(dir == WALK_LEFT ? position.x - 1 : position.x + 1));
	int thisY =	LevelFacade->getHeightForXPos(round(position.x));

	if (abs(nextY - thisY) >= 2.0f) {
		return true;
	}

	return false;
}

/// <summary>
/// Checks if the object has reached either starting or end area
/// </summary>
/// <param name="dir">direction the object currently faces</param>
/// <param name="start">true if it should be checked for the starting area</param>
/// <returns>true if the object has reached the questioned area</returns>
bool MovingObject::checkForReachedArea(MovingObjectStatus dir, bool start) {
	if (dir != WALK_LEFT && dir != WALK_RIGHT) {
		return false;
	}

	int posX = dir == WALK_RIGHT ? ceil(position.x) : floor(position.x);
	int currY = ceil(position.y) - 1;
	int nextY = ceil(position.y) - 2;
	TileLocation loc = start ? START_AREA : END_AREA;

	return LevelFacade->checkForSpecificArea(posX, currY, loc) ||
		LevelFacade->checkForSpecificArea(posX, nextY, loc);
}

/// <summary>
/// Resets this object for a new game
/// </summary>
void MovingObject::reset() {
	_hitbox.setOrigin(startPos);
	position = startPos;
	status = STAND;
	wasOnGround = true;
	isOnGround = true;
	hasCeiling = false;
	hasTileLeft = false;
	hasTileRight = false;
}

/// <summary>
/// Returns the hitbox of the object as a bounding box.
/// </summary>
AABB MovingObject::getHitbox() {
	return _hitbox;
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