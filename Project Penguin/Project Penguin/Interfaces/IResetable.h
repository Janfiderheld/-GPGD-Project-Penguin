#ifndef RESET_INTERACE
#define RESET_INTERACE

#include <GLM/glm.hpp>

class IResetable {
protected:
	glm::vec3 startPos;

public:
	virtual void reset() = 0;
};

#endif // RESET_INTERACE