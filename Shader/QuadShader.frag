#version 400 core

in vec2 qCoords[8];
in vec2 textureCoords;

layout(location = 0) out vec3 outColor;


uniform sampler2D lookUpTexture;
uniform float PMsz;
uniform float tanPhi;

void main()
{ 
	vec2 qScreenCoords[8];
	float c;
	vec3 cMax = texture(lookUpTexture, textureCoords.xy).rgb;
	//z = texture(lookUpTexture, gl_FragCoord.xy).b;
	float z = cMax.z;
	float m = -(PMsz + z)/tanPhi;

	for (int i=0; i<8; ++i) {
		qScreenCoords[i] = texture(lookUpTexture, qCoords[i]).rg;
		
		//c = z - m*sqrt(pow(gl_FragCoord.x-qScreenCoords[i].x,2)+pow(gl_FragCoord.y-qScreenCoords[i].y,2));
		c = z - m*sqrt(pow(textureCoords.x-qScreenCoords[i].x,2)+pow(textureCoords.y-qScreenCoords[i].y,2));
		if (c>cMax.z) {
			cMax.z = c;
			cMax.xy = qScreenCoords[i];
		}
	}
	outColor = cMax;

	// Debugging
	//outColor = texture(lookUpTexture, textureCoords).rgb;
    //outColor = vec3(textureCoords.x,textureCoords.y,0);

	//gl_FragColor = cMax;
}