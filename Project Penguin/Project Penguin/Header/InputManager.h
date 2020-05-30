#ifndef INPUTMAN_HEADER
#define INPUTMAN_HEADER

#include <InputDirection.h>

class InputManager {
private:
	bool currInputs[3];
	bool prevInputs[3];

public:
	InputManager();

	void Update();

	bool justPressed(InputDirection keyDirect);
	bool justReleased(InputDirection keyDirect);
	bool getInputStatus(InputDirection keyDirect);
	void setInputStatus(InputDirection keyDirect, bool val);
};

#endif // INPUTMAN_HEADER