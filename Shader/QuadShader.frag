#version 400 core

in vec2 qCoords[8]; // unit coordinate between 0 and 1
in vec2 textureCoords; // unit coordinate between 0 and 1

layout(location = 0) out vec3 outColor;


uniform sampler2D lookUpTexture;
uniform float PMsz;
uniform float tanPhiInv;


vec3 getDepthAndCoordinateMax()
{
	//vec3 depthAndCoordinateMax;
	//depthAndCoordinateMax.xy = textureCoords;
	//float zMax = texture(lookUpTexture, textureCoords.xy).b;

	vec3 depthAndCoordinateMax = texture(lookUpTexture, textureCoords.xy).rgb;
	float zMax = depthAndCoordinateMax.z;
	
	for (int i=0; i<9; ++i) {
		float z = texture(lookUpTexture, qCoords[i].xy).b;
		if (z>zMax) {
			zMax = z;
			depthAndCoordinateMax = texture(lookUpTexture, textureCoords.xy).rgb;
		}
	}
	return depthAndCoordinateMax;
}

vec3 calcCAndCoordinate(float z, vec2 textureCoords, vec2 qCoords)
{
	vec3 cAndCoordinate;

	//vec2 textureCoordinates = textureCoords;
	//vec2 qCoordinates = qCoords;
	
	vec2 textureCoordinates = texture(lookUpTexture, textureCoords).rg;
	vec2 qCoordinates = texture(lookUpTexture, qCoords).rg;

	float m =  tanPhiInv;
	float c = z - m*sqrt(pow(textureCoordinates.x - qCoordinates.x,2)+pow(textureCoordinates.y - qCoordinates.y,2));

	cAndCoordinate.xy = qCoordinates;
	cAndCoordinate.z = c;

	return cAndCoordinate;
}

void main()
{ 
	vec3 zAndCoordMax = getDepthAndCoordinateMax();
	
	for (int i=0; i<9; ++i)
	{
		vec3 cAndCoordinateAct = calcCAndCoordinate(zAndCoordMax.z, textureCoords, qCoords[i]);
		if(cAndCoordinateAct.z > zAndCoordMax.z)
		{
			zAndCoordMax = cAndCoordinateAct;
		}
	}
	outColor = zAndCoordMax;

	/*
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
	outColor = cMax;
	*/

	// Debugging
	//outColor = texture(lookUpTexture, textureCoords).rgb;
    //outColor = vec3(textureCoords.x,textureCoords.y,0);

	//gl_FragColor = cMax;
}