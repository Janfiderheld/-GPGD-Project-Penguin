#version 330 core
in vec2 texCoord;
in vec4 worldPos;

uniform sampler2D ice;
uniform sampler2D desert;
uniform sampler2D iceBorder;
uniform sampler2D desertBorder;

uniform float barrierPos;
uniform bool isStart;
uniform bool isEnd;
uniform bool borderUp;

out vec4 FragColor;

void main()
{
	vec4 fullTexture = vec4(1.0);
	vec4 borderTexture = vec4(1.0);

	// draw either ice or desert texture
	if(worldPos.x >= barrierPos) {		
		fullTexture = texture(ice, texCoord);
		borderTexture = texture(iceBorder, texCoord);
	} else {
		fullTexture = texture(desert, texCoord);		
		borderTexture = texture(desertBorder, texCoord);
	}		

	// draw border with alpha blending
	if(borderUp && !isStart && !isEnd) {
		FragColor = fullTexture * (1 - borderTexture.a) + borderTexture * borderTexture.a;
	} else {
		FragColor = fullTexture;
	}

	// draw start & end markings
	if(isStart && texCoord.y >= 0.96) {
		FragColor = vec4(1.0, 0.84, 0.0, 1.0);
	}

	if(isEnd && texCoord.y >= 0.96) {
		FragColor = vec4(0.0, 1.0, 0.16, 1.0);
	}	
}