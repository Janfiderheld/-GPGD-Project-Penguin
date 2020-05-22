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

void MovingObject::UpdatePhysics()
{
	oldPosition = position;
	oldSpeed = speed;
	wasOnGround = isOnGround;
	hadTileLeft = hasTileLeft;
	hadTileRight = hasTileRight;

	for (int i = 0; i < 3; i++) {
		prevInputs[i] = currInputs[i];
	}

	isOnGround = Facade->checkForGround(floor(position.x), floor(position.y), _hitbox);
	hasTileLeft = Facade->checkForLeftWall(floor(position.x), floor(position.y), _hitbox);;
	hasTileRight = Facade->checkForRightWall(floor(position.x), floor(position.y), _hitbox);;
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