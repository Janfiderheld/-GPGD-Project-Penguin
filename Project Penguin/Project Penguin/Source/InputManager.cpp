#include <InputManager.h>

/// <summary>
/// Initializes the InputManager by setting all Inputs to false
/// </summary>
InputManager::InputManager() {
	for (int i = 0; i < 3; i++) {
		currInputs[i] = false;
	}
}

/// <summary>
/// Returns the current status for the given Input Direction. True means key is pressed
/// </summary>
/// <param name="keyDirect">key direction to look for (UP, LEFT or RIGHT)</param>
bool InputManager::getInputStatus(InputDirection keyDirect) {
	return currInputs[keyDirect];
}

/// <summary>
/// Sets the status for the given input direction
/// </summary>
/// <param name="keyDirect">key direction to change</param>
/// <param name="val">new value to save</param>
void InputManager::setInputStatus(InputDirection keyDirect, bool val) {
	currInputs[keyDirect] = val;
}