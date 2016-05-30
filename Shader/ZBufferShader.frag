// FRAGMENT SHADER calculate distance to light for each fragment
#version 400 core

layout(location = 0) out vec3 outColor;
uniform vec2 texDim;


void main() {
	// Screen space coordinates
	outColor.r = gl_FragCoord.x/texDim.x;
	outColor.g = gl_FragCoord.y/texDim.y;

	// Depth values
	outColor.b = gl_FragCoord.z;
	
}