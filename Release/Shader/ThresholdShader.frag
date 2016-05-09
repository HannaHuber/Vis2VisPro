#version 400 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

void main()
{ 
	//float thresholdSingle = 0.995; // if one (or more) color channels have a value above this threshold it is accepted
	//float thresholdAll = 0.97; // or if all of the 3 channels have a value above this threshold
	float threshold = 0.75;
	//color = vec4(0,0,0,1);
	/*vec4 thisPixel = textureLod(screenTexture, TexCoords.st, 1);
if(thisPixel.r >= thresholdSingle || thisPixel.g >= thresholdSingle || thisPixel.b >= thresholdSingle ){
	color = thisPixel;
}else if(thisPixel.r >= thresholdAll && thisPixel.g >= thresholdAll && thisPixel.b >= thresholdAll){
	color = thisPixel;
}*/
vec4 reducedColor = textureLod(screenTexture, TexCoords.st, 9)-vec4(threshold);
color.r = max(0,reducedColor.r);
color.g = max(0,reducedColor.g);
color.b = max(0,reducedColor.b);
color.a = 1;
}