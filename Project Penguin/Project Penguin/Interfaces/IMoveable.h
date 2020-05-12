enum MovementDirection {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class IMovable {
private:
	float _speed = 2.0f;

public:
	virtual void calculatePosition(MovementDirection dir, float deltaTime) = 0;

	float getSpeed() {
		return _speed;
	}

	void setSpeed(float newSpeed) {
		_speed = newSpeed;
	}
};