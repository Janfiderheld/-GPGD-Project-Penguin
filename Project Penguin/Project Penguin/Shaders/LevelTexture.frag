#version 330 core
in vec2 texCoord;
in vec4 worldPos;

uniform sampler2D ice;
uniform sampler2D desert;

uniform float barrierPos;
uniform bool isStart;
uniform bool isEnd;

uniform bool borderLeft;
uniform bool borderRight;
uniform bool borderUp;
uniform bool borderDown;

out vec4 FragColor;

void main()
{
	float upperStart = 0.96;
	float lowerEnd = 0.04;

	// draw either ice or desert texture
	if(worldPos.x < barrierPos) {		
		FragColor = texture(desert, texCoord);
	} else {
		FragColor = texture(ice, texCoord);
	}	

	// draw borders
	if((borderLeft && texCoord.x <= lowerEnd) ||
	   (borderRight && texCoord.x >= upperStart) ||
	   (borderUp && texCoord.y >= upperStart) ||
	   (borderDown && texCoord.y <= lowerEnd)) {
		FragColor = vec4(0.0, 0.0, 0.9, 1.0);
	}

	// draw start & end markings
	if(isStart && texCoord.y >= upperStart) {
		FragColor = vec4(1.0, 0.84, 0.0, 1.0);
	}

	if(isEnd && texCoord.y >= upperStart) {
		FragColor = vec4(0.0, 1.0, 0.16, 1.0);
	}	
}