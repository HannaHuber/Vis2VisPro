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
    //gl_Position = view_proj * model * vec4(position.x, position.y, 0, 1); 
	gl_Position = vec4(position.x, position.y, 0, 1); 

	qCoords[0] = vec2(gl_Position.x + step, gl_Position.y - step);
	qCoords[1] = vec2(gl_Position.x + step, gl_Position.y );
	qCoords[2] = vec2(gl_Position.x + step, gl_Position.y + step);

	qCoords[3] = vec2(gl_Position.x, gl_Position.y - step);
	qCoords[4] = vec2(gl_Position.x, gl_Position.y + step);

	qCoords[5] = vec2(gl_Position.x - step, gl_Position.y - step);
	qCoords[6] = vec2(gl_Position.x - step, gl_Position.y );
	qCoords[7] = vec2(gl_Position.x - step, gl_Position.y + step);

	textureCoords = texCoords;
	float x_step = step/1024.0;
	float y_step = step/800.0;

	qCoords[0] = vec2(texCoords.x + x_step, texCoords.y - y_step);
	qCoords[1] = vec2(texCoords.x + x_step, texCoords.y );
	qCoords[2] = vec2(texCoords.x + x_step, texCoords.y + y_step);

	qCoords[3] = vec2(texCoords.x, texCoords.y - y_step);
	qCoords[4] = vec2(texCoords.x, texCoords.y + y_step);

	qCoords[5] = vec2(texCoords.x - x_step, texCoords.y - y_step);
	qCoords[6] = vec2(texCoords.x - x_step, texCoords.y );
	qCoords[7] = vec2(texCoords.x - x_step, texCoords.y + y_step);

} 