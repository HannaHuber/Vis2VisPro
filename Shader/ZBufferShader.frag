// FRAGMENT SHADER calculate distance to light for each fragment
#version 400 core

//layout(location = 0) out vec3 outColor;
layout(location = 0) out vec2 outColor;
uniform vec2 texDim;


void main() {
	// Screen space coordinates
	outColor.r = gl_FragCoord.x/texDim.x;
	outColor.g = gl_FragCoord.y/texDim.y;

	// Depth values
	//gl_FragDepth = gl_FragCoord.z;
	//outColor.b = gl_FragCoord.z;
	
}