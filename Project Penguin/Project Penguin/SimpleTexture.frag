#version 330 core
in vec2 texCoord;
in vec4 worldPos;

out vec4 FragColor;

uniform sampler2D normal;
uniform sampler2D changed;

uniform bool drawTexture;
uniform bool changeTexture;
uniform float barrierPos;

void main()
{
	if(drawTexture) {	
		if(worldPos.x < barrierPos && changeTexture) {		
			FragColor = texture(changed, texCoord);
		} else {
			FragColor = texture(normal, texCoord);
		}
	} else {
		FragColor = vec4(0.0f, 0.85f, 0.1f, 0.5f);
	}
}