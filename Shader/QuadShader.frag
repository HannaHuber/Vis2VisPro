#version 400 core

in vec2 qCoords[8];
in vec2 textureCoords;

//layout(location = 0) out vec3 outColor;
layout(location = 0) out vec2 outColor;

//uniform sampler2D lookUpTexture;
uniform sampler2D posTexture;
uniform sampler2D depthTexture;
uniform float PMsz;
uniform float tanPhiInv;

void main()
{ 
	vec2 qScreenCoords[8];
	float c, m;
	vec3 cMax = vec3(texture(posTexture, textureCoords.xy).rg, texture(depthTexture, textureCoords.xy));
	//vec3 cMax = texture(lookUpTexture, textureCoords.xy).rgb;
	//z = texture(lookUpTexture, gl_FragCoord.xy).b;
	float z = cMax.z;
	float zMax = z;

	for (int i=0; i<9; ++i) {
		//qScreenCoords[i] = texture(lookUpTexture, qCoords[i]).rg;
		qScreenCoords[i] = texture(posTexture, qCoords[i]).rg;
		//z = texture(lookUpTexture, qCoords[i]).b;
		z = texture(depthTexture, qCoords[i]).x;
		if (z>zMax) {
			zMax = z;
		}
	}

	for (int i=0; i<9; ++i) {
		//qScreenCoords[i] = texture(lookUpTexture, qCoords[i]).rg;
		qScreenCoords[i] = texture(posTexture, qCoords[i]).rg;
		z = zMax; // texture(lookUpTexture, qCoords[i]).b;
		m =  tanPhiInv; //(-1)*(PMsz + z)*tanPhiInv; 1;max(0.5,)
		//c = z - m*sqrt(pow(gl_FragCoord.x-qScreenCoords[i].x,2)+pow(gl_FragCoord.y-qScreenCoords[i].y,2));
		c = z - m*sqrt(pow(textureCoords.x-qScreenCoords[i].x,2)+pow(textureCoords.y-qScreenCoords[i].y,2));
		//c = z - m*max(abs(textureCoords.x-qScreenCoords[i].x),abs(textureCoords.y-qScreenCoords[i].y));
		if (c>cMax.z) {
			cMax.z = c;
			//zMax = z;
			cMax.xy = qScreenCoords[i];
		}
	}
	outColor = cMax.xy;
	gl_FragDepth = cMax.z;

	// Debugging
	//outColor = texture(lookUpTexture, textureCoords).rgb;
    //outColor = vec3(textureCoords.x,textureCoords.y,0);

	//gl_FragColor = cMax;
}