#version 330 core
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D text;
uniform bool drawTexture;

void main()
{
	if(drawTexture) {	
		FragColor = texture(text, texCoord);
	} else {
		FragColor = vec4(0.0f, 0.85f, 0.1f, 0.5f);
	}
}