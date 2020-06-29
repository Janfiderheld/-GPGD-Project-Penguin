#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec4 worldPos;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0f);
	texCoord = vec2(tex.x, tex.y);
	worldPos = model * vec4(pos, 1.0f);
}