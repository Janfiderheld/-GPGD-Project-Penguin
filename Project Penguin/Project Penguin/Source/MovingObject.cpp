#include <MovingObject.h>

GridFacade* MovingObject::Facade = nullptr;

// Constructor, which sets the texture and the position
MovingObject::MovingObject(glm::vec3 pos, Texture texture, AABB boundBox) : _texture(texture), _hitbox(boundBox)
{
	position = pos;	
	for (int i = 0; i < 3; i++) {
		currInputs[i] = false;
		prevInputs[i] = false;
	}
}

void MovingObject::UpdatePhysics(float deltaTime)
{
	oldPosition = position;
	oldSpeed = speed;
	wasOnGround = isOnGround;
	hadTileLeft = hasTileLeft;
	hadTileRight = hasTileRight;

	for (int i = 0; i < 3; i++) {
		prevInputs[i] = currInputs[i];
	}

	position += speed * deltaTime;
	_hitbox.setOrigin(position);

	int flooredPosX = floor(position.x);
	int flooredPosY = floor(position.y);
	int roundPosX = round(position.x);
	int roundPosY = round(position.y);
	int ceilPosX = ceil(position.x);
	int ceilPosY = ceil(position.y);

	bool twoBottoms = Facade->checkForTwoTilesInX(flooredPosX, ceilPosY - 1, _hitbox);
	bool twoCeilings = Facade->checkForTwoTilesInX(flooredPosX, flooredPosY + 2, _hitbox);
	bool twoRight = Facade->checkForTwoTilesInY(flooredPosX + 1, flooredPosY, _hitbox);
	bool twoLeft = Facade->checkForTwoTilesInY(ceilPosX - 1, flooredPosY, _hitbox);

	bool bottomTileLeft = Facade->checkForWall(flooredPosX, ceilPosY - 1);
	bool bottomTileRight = Facade->checkForWall(ceilPosX, ceilPosY - 1);
	bool upperTileLeft = Facade->checkForWall(flooredPosX, flooredPosY + 2);
	bool upperTileRight = Facade->checkForWall(ceilPosX, flooredPosY + 2);

	bool leftWallLower = Facade->checkForWall(ceilPosX - 1, flooredPosY);
	bool leftWallUpper = Facade->checkForWall(ceilPosX - 1, ceilPosY);
	bool rightWallLower = Facade->checkForWall(flooredPosX + 1, flooredPosY);
	bool rightWallUpper = Facade->checkForWall(flooredPosX + 1, ceilPosY);

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

	bool clampUpperLeft = Facade->checkForWall(flooredPosX, flooredPosY + 1);
	bool clampUpperRight = Facade->checkForWall(ceilPosX, flooredPosY + 1);
	bool clampJump = false;
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

AABB MovingObject::getHitbox()
{
	return _hitbox;
}

Texture MovingObject::getTexture()
{
	return _texture;
}

glm::vec3 MovingObject::getPosition() {
	return position;
}

bool MovingObject::justPressed(Direction keyDirect) {
	if (keyDirect != DOWN) {
		return currInputs[keyDirect] && !prevInputs[keyDirect];
	} else {
		return false;
	}	
}

bool MovingObject::justReleased(Direction keyDirect) {
	if (keyDirect != DOWN) {
		return !currInputs[keyDirect] && prevInputs[keyDirect];
	}
	else {
		return false;
	}
}

bool MovingObject::getInputStatus(Direction keyDirect) {
	if (keyDirect != DOWN) {
		return currInputs[keyDirect];
	}
	else {
		return false;
	}
}

void MovingObject::setInputStatus(Direction keyDirect, bool val) {
	if (keyDirect != DOWN) {
		currInputs[keyDirect] = val;
	}
}