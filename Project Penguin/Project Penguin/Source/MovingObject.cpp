#include <MovingObject.h>

GridFacade* MovingObject::Facade = nullptr;

// Constructor, which sets the texture and the position
MovingObject::MovingObject(glm::vec3 pos, Texture texture, AABB boundBox) : _texture(texture), _hitbox(boundBox)
{
	position = pos;	
	centerOffset = glm::vec3(boundBox.getWidth() / 2.0f, boundBox.getHeight() / 2.0f, 0.0f);
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

	int flooredPosX = floor(position.x + centerOffset.x);
	int flooredPosY = floor(position.y + centerOffset.y);
	int ceilPosX = ceil(position.x + centerOffset.x);
	int ceilPosY = ceil(position.y + centerOffset.y);
	int roundPosX = round(position.x + centerOffset.x);
	int roundPosY = round(position.y + centerOffset.y);

	isOnGround = Facade->checkForGround(flooredPosX, flooredPosY, _hitbox);
	hasTileLeft = Facade->checkForLeftWall(roundPosX, roundPosY, _hitbox);
	hasTileRight = Facade->checkForRightWall(flooredPosX, flooredPosY, _hitbox);
	hasCeiling = Facade->checkForCeiling(flooredPosX, flooredPosY, _hitbox);
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