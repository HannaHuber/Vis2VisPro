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
	float m, z, c;
	vec3 cMax = vec3(-1, -1, -1);
	for (int i=0; i<8; ++i) {
		qScreenCoords[i] = texture(lookUpTexture, qCoords[i]).rg;
		z = texture(lookUpTexture, gl_FragCoord.xy).b;
		m = -(PMsz + z)/tanPhi;
		c = z - m*sqrt(pow(gl_FragCoord.x-qScreenCoords[i].x,2)+pow(gl_FragCoord.y-qScreenCoords[i].y,2));
		if (c>cMax.z) {
			cMax.z = c;
			cMax.xy = qScreenCoords[i];
		}
	}
	outColor = cMax;

	// Debugging
	//outColor = vec3(texture(lookUpTexture, textureCoords).r/1024.0, texture(lookUpTexture, textureCoords).r/1024.0, texture(lookUpTexture, textureCoords).r/1024.0);
    //outColor = vec3(100,200,500);

	//gl_FragColor = cMax;
}