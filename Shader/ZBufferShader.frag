// FRAGMENT SHADER calculate distance to light for each fragment
#version 400 core

layout(location = 0) out vec4 outColor;


void main() {
	// Screen space coordinates
	
	// CBR
	//outColor.r = gl_FragCoord.x/1024;
	outColor.r = gl_FragCoord.x;
	outColor.g = gl_FragCoord.y;

	// Depth values
	outColor.b = gl_FragCoord.z;
	
}