#version 330 core
uniform mat4 VP;
uniform int height;
uniform int width;

uniform int lightRadius;
uniform vec3 lightLocation;
uniform vec4 lightColor;

out vec4 FragColor;

void main()
{
	vec4 lightInView = VP * vec4(lightLocation, 1.0);
	vec3 lightDehom = vec3(lightInView.rgb / lightInView.w);
	vec2 lightOnScreen = vec2(((lightDehom.x * 0.5) + 0.5) * width, ((lightDehom.y * 0.5) + 0.5) * height);	
	
	float distance = length(lightOnScreen.xy - gl_FragCoord.xy);
	float radiusF = float(lightRadius);
	float maxRadius = (radiusF / 100) * height;

	if(distance >= maxRadius) {
		FragColor = vec4(0.0);
	} else {
		float attenuation = 1.0 - sqrt(distance / maxRadius);
		float alpha = pow(distance / maxRadius, 3.0);
		FragColor = vec4(attenuation, attenuation, attenuation, alpha) * lightColor;
	}
}