#version 330 core
uniform mat4 VP;
uniform int height;
uniform int width;

uniform bool drawLight;

uniform vec3 barrierPos; 
uniform float barrierSize;

uniform int lightRadius;
uniform vec4 lightColor;

out vec4 FragColor;

void main()
{
	vec4 barrierInView = VP * vec4(barrierPos, 1.0);
	vec3 barrierDehom = vec3(barrierInView.rgb / barrierInView.w);
	vec2 barrierOnScreen = vec2(((barrierDehom.x * 0.5) + 0.5) * width, ((barrierDehom.y * 0.5) + 0.5) * height);	
	
	float distance = gl_FragCoord.x - barrierOnScreen.x;
	float radiusF = float(lightRadius);
	float maxRadius = (radiusF / 100) * width;

	if(drawLight) {
		if(distance <= maxRadius) {
			float attenuation = 1.0 - sqrt(distance / maxRadius);
			float alpha = pow(distance / maxRadius, 3.0);
			FragColor = vec4(attenuation, attenuation, attenuation, alpha) * lightColor;
		} else {
			FragColor = vec4(0.0);
		}	
	} else {
		if(gl_FragCoord.x <= barrierOnScreen.x && gl_FragCoord.x >= barrierOnScreen.x - barrierSize) {	
			FragColor = vec4(0.0f, 1.0f, 0.1f, 0.8f);
		} else {
			FragColor = vec4(0.0);
		}
	}	
}