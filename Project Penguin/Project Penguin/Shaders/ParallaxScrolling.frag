#version 330 core
uniform mat4 VP;
uniform int width;
uniform int height;

uniform int maxWidth;
uniform int maxHeight;

uniform int layerNo;
uniform vec3 camPos;
uniform vec3 barrierPos; 

uniform sampler2D ice;
uniform sampler2D desert;

out vec4 FragColor;

void main()
{
	vec4 barrierInView = VP * vec4(barrierPos, 1.0);
	vec3 barrierDehom = vec3(barrierInView.rgb / barrierInView.w);
	vec2 barrierOnScreen = vec2(((barrierDehom.x * 0.5) + 0.5) * width, ((barrierDehom.y * 0.5) + 0.5) * height);

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

	if(gl_FragCoord.x <= barrierOnScreen.x) {	
		FragColor = texture(desert, texCoords);
	} else {
		FragColor = texture(ice, texCoords);
	}
}