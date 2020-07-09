#version 330 core
in vec2 texCoord;
in vec4 worldPos;

uniform sampler2D normal;

out vec4 FragColor;

void main()
{
	FragColor = texture(normal, texCoord);
}