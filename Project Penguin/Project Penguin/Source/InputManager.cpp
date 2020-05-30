#include <InputManager.h>

InputManager::InputManager() {
	for (int i = 0; i < 3; i++) {
		currInputs[i] = false;
		prevInputs[i] = false;
	}
}

void InputManager::Update() {
	for (int i = 0; i < 3; i++) {
		prevInputs[i] = currInputs[i];
	}
}

bool InputManager::justPressed(InputDirection keyDirect) {
	if (keyDirect != DOWN) {
		return currInputs[keyDirect] && !prevInputs[keyDirect];
	} else {
		return false;
	}
}

bool InputManager::justReleased(InputDirection keyDirect) {
	if (keyDirect != DOWN) {
		return !currInputs[keyDirect] && prevInputs[keyDirect];
	} else {
		return false;
	}
}

bool InputManager::getInputStatus(InputDirection keyDirect) {
	if (keyDirect != DOWN) {
		return currInputs[keyDirect];
	} else {
		return false;
	}
}

void InputManager::setInputStatus(InputDirection keyDirect, bool val) {
	if (keyDirect != DOWN) {
		currInputs[keyDirect] = val;
	}
}