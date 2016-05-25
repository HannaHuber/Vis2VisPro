#version 400 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoords;

out vec2 qCoords[8];
out vec2 textureCoords;

uniform mat4 model;
uniform mat4 view_proj; 

uniform int step;

void main()
{
	// Clip space position [-1,1]
    gl_Position = view_proj * model * vec4(position.x, position.y, 0, 1); 

	// Shift to [1,w+1]x[1,h+1]
	vec2 shift_pos = (gl_Position.xy*0.5 + 0.5) * vec2(1024,800) + 1;

	// Calculate neighbors
	vec2 p = shift_pos;

	qCoords[0] = vec2(p.x + step,p.y - step);
	qCoords[1] = vec2(p.x + step, p.y );
	qCoords[2] = vec2(p.x + step, p.y + step);

	qCoords[3] = vec2(p.x, p.y - step);
	qCoords[4] = vec2(p.x, p.y + step);

	qCoords[5] = vec2(p.x - step,p.y - step);
	qCoords[6] = vec2(p.x - step, p.y );
	qCoords[7] = vec2(p.x - step, p.y + step);

	textureCoords = texCoords;

} 