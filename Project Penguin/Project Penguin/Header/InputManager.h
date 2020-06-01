#ifndef INPUTMAN_HEADER
#define INPUTMAN_HEADER

#include <InputDirection.h>

class InputManager {
private:
	bool currInputs[3];

public:
	InputManager();

	bool getInputStatus(InputDirection keyDirect);
	void setInputStatus(InputDirection keyDirect, bool val);
};

#endif // INPUTMAN_HEADER