#version 330 core
in vec2 texCoord;
in vec4 worldPos;

uniform sampler2D normal;
uniform sampler2D changed;

uniform bool changeTexture;
uniform float barrierPos;

out vec4 FragColor;

void main()
{
	if(worldPos.x < barrierPos && changeTexture) {		
		FragColor = texture(changed, texCoord);
	} else {
		FragColor = texture(normal, texCoord);
	}
}