#version 330 core
uniform int width;
uniform int height;

uniform int maxWidth;
uniform int maxHeight;

uniform int layerNo;
uniform vec3 camPos;

uniform sampler2D normal;

out vec4 FragColor;

void main()
{
	float ratio = width / height;
	float widthScreen = 0.4;
	float heightScreen = widthScreen / ratio;

	float currentCamX = (camPos.x / maxWidth) * (1.0 - (layerNo * 0.1));
	float currentCamY = (camPos.y / maxHeight) + 0.25;
	vec2 texCoords = vec2(gl_FragCoord.x / (width - 1), gl_FragCoord.y / (height - 1));	
	texCoords.x = widthScreen * texCoords.x + currentCamX - (widthScreen / 2);
	texCoords.y = heightScreen * texCoords.y + currentCamY - (heightScreen / 2);

	if(texCoords.x > 1.0) {
		texCoords.x = texCoords.x - 1.0;
	}
	if(texCoords.y > 1.0) {
		texCoords.y = texCoords.y - 1.0;
	}

	FragColor = texture(normal, texCoords);
}