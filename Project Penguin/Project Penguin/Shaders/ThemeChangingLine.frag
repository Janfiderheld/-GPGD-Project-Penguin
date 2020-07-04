#version 330 core
uniform mat4 VP;
uniform int height;
uniform int width;

uniform vec3 barrierPos; 
uniform float barrierSize;

out vec4 FragColor;

void main()
{
	vec4 barrierInView = VP * vec4(barrierPos, 1.0);
	vec3 barrierDehom = vec3(barrierInView.rgb / barrierInView.w);
	vec2 barrierOnScreen = vec2(((barrierDehom.x * 0.5) + 0.5) * width, ((barrierDehom.y * 0.5) + 0.5) * height);	
	
	if(gl_FragCoord.x <= barrierOnScreen.x && gl_FragCoord.x >= barrierOnScreen.x - barrierSize) {	
		FragColor = vec4(0.0f, 1.0f, 0.1f, 0.8f);
	} else {
		FragColor = vec4(0.0);
	}
}