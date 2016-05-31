#version 400 core
in vec3 worldNormal;
in vec4 worldPos4D;
in vec3 viewVector;

uniform int light_count;
uniform vec3 light_location[20]; //Note: not more than 20 lights are allowed
uniform vec3 light_intensity[20];
uniform vec3 light_attenuation[20];

struct Material {
	vec3 ambient_color;
	vec3 diffuse_color;
	vec3 specular_color;
	float shininess;
	float transparency;
};
uniform Material material;

// Cutaway
uniform sampler2D cutaway_surface;
uniform float clip;
uniform vec2 texDim;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 worldPos = worldPos4D.xyz;

	outColor = vec4(0,0,0,0);
	vec3 ambient_color = material.ambient_color;
	vec3 diffuse_color = material.diffuse_color;
	vec3 specular_color = material.specular_color;
	float shininess = material.shininess;
	normalize(viewVector);
	normalize(worldNormal);	

	bool draw = true;
	if (clip>0.5) {
		// Debug
		float px = gl_FragCoord.x/texDim.x;
		float py = gl_FragCoord.y/texDim.y;
		float pz = gl_FragCoord.z;

		vec3 p = gl_FragCoord.xyz * 0.5 + 0.5;
		float cutaway_depth = texture(cutaway_surface, vec2(px,py)).b;
		//float disc = texture(cutaway_surface, vec3(px,py, pz), 0.01);

		// Debug
		//vec3 cutaway_col = texture(cutaway_surface, vec2(px,py)).rgb;
		//outColor = vec4(cutaway_depth, cutaway_depth, cutaway_depth, 1);
		//outColor = vec4(pz, pz, cutaway_depth, 1);
		//outColor = vec4(cutaway_col.b, cutaway_col.b, cutaway_depth, 1);
		//draw = false;

		if (pz < cutaway_depth ) {
		//if (disc==0.0) {
			draw = false;
			discard;
		}
	}
	
	if (draw) {
		// Iterate over all light sources
		for(int i = 0; i < light_count; i++){

			vec3 light_dir = light_location[i]-worldPos;
			vec3 L = normalize(light_dir); // Vector from position(fragment) to light source
			vec3 H = normalize(L+viewVector);
		
			float d = length(light_dir);									// Distance between pos and point light
			float a = light_attenuation[i].x + d*light_attenuation[i].y + d*d*light_attenuation[i].z;// Attenuation
			vec3 I = light_intensity[i] / a;													// Intensity

			float NdotL = max(dot(worldNormal,L),0.0);
			float NdotH = max(dot(worldNormal,H),0.0);
			if(material.transparency < 1){
			NdotL = abs(dot(worldNormal,L));
			NdotH = abs(dot(worldNormal,H));
			}
			vec3 color = diffuse_color*NdotL + specular_color*NdotL*pow(NdotH,shininess);

			vec3 illumination = I*(color) + ambient_color;
				
			outColor = outColor+vec4(illumination, 1);
		}

		// Scale out_color to [0,1]
		if (max(outColor.x, max(outColor.y, outColor.z))>1) {
			outColor = outColor * 1.0/max(outColor.x, max(outColor.y, outColor.z));
		}

		outColor = vec4(outColor.xyz,material.transparency);
	}
	
	
	
		
}