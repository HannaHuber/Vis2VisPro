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
	float c, m;
	vec3 cMax = texture(lookUpTexture, textureCoords.xy).rgb;
	//z = texture(lookUpTexture, gl_FragCoord.xy).b;
	float z = cMax.z;
	float zMax = z;

	for (int i=0; i<9; ++i) {
		qScreenCoords[i] = texture(lookUpTexture, qCoords[i]).rg;
		z = texture(lookUpTexture, qCoords[i]).b;
		if (z>zMax) {
			zMax = z;
		}
	}

	for (int i=0; i<9; ++i) {
		qScreenCoords[i] = texture(lookUpTexture, qCoords[i]).rg;
		z = zMax; // texture(lookUpTexture, qCoords[i]).b;
		m =  1; //-(PMsz + z)/tanPhi;
		//c = z - m*sqrt(pow(gl_FragCoord.x-qScreenCoords[i].x,2)+pow(gl_FragCoord.y-qScreenCoords[i].y,2));
		c = z - m*sqrt(pow(textureCoords.x-qScreenCoords[i].x,2)+pow(textureCoords.y-qScreenCoords[i].y,2));
		//c = z - m*max(abs(textureCoords.x-qScreenCoords[i].x),abs(textureCoords.y-qScreenCoords[i].y));
		if (c>cMax.z) {
			cMax.z = c;
			//zMax = z;
			cMax.xy = qScreenCoords[i];
		}
	}
	outColor = cMax;

	// Debugging
	//outColor = texture(lookUpTexture, textureCoords).rgb;
    //outColor = vec3(textureCoords.x,textureCoords.y,0);

	//gl_FragColor = cMax;
}