#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D baseTexture;
uniform sampler2D bloom;

void main()
{
	color = texture(baseTexture, TexCoords) + texture(bloom, TexCoords); 
	//color = texture(bloom, TexCoords);
}