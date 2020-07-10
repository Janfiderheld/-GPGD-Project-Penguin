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
	if(borderUp) {
		if(isStart) {
			borderTexture = borderTexture * vec4(0.17, 0.0, 1.0, 1.0);
		}
		if(isEnd) {
			borderTexture = borderTexture * vec4(0.0, 1.0, 0.16, 1.0);
		}
		FragColor = fullTexture * (1 - borderTexture.a) + borderTexture * borderTexture.a;
	} else {
		FragColor = fullTexture;
	}	
}