#version 440

in vec4 Position;
in vec3 Normal;
in vec4 LightSpacePos;

// Define structures
struct LightInfo {
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
};

struct MaterialInfo {
	vec3 Ka;
	vec3 Kd;
	vec3 Ks;
	float Shiness;
};

struct SpotLightInfo {
	vec4 Position;
	vec3 La;
	vec3 Ld;
	vec3 Ls;
	vec3 Direction;
	float Exponent;
	float Cutoff;
};

// Uniform values
uniform LightInfo PointLights[5];
uniform MaterialInfo Material;
uniform SpotLightInfo SpotLight[5];

uniform sampler2D depthMap;

out vec4 FragColor;

float ShadowCalculation(vec4 LightSpacePos)
{
    vec3 projCoords = LightSpacePos.xyz / LightSpacePos.w;
    projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(depthMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	vec3 L = normalize(vec3(PointLights[0].Position - Position));
	float bias = max(0.05 * (1.0 - dot(Normal, L)), 0.005);
	float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

	return shadow;
}

void main() {
	vec3 finalColor = vec3(0,0,0);
	vec3 ambient = PointLights[0].La * Material.Ka;

	for (int i=0; i<5; i++)
	{
		vec3 L = normalize(vec3(PointLights[i].Position - Position));
	
		vec3 R = normalize(reflect(-L,Normal));
		vec3 V = normalize(vec3(-Position));

		vec3 H = normalize(V + L);

		
		vec3 diffuse = PointLights[i].Ld * Material.Kd * max(dot(L,Normal),0);
		vec3 spec = PointLights[i].Ls * Material.Ks * pow(max(dot(Normal, H), 0.0), Material.Shiness);

		finalColor = finalColor +  diffuse + spec;
	}

	//finalColor = vec3(0,0,0); // IGNORE GLOBAL LIGHTING FOR DEBUG PURPOSE

	//for (int i=0; i<5; i++)
	//{
	//	vec3 L = normalize(vec3(SpotLight[i].Position - Position));
	//
	//	vec3 R = normalize(reflect(-L,Normal));
	//	vec3 V = normalize(vec3(-Position));
	//
	//	vec3 H = normalize(V + L);
	//
	//	float spotEffect = pow(dot(-L, SpotLight[i].Direction), SpotLight[i].Exponent);
	//	vec3 sp = normalize(-L);
	//	float sp_dot_d = dot(sp, SpotLight[i].Direction);
	//	float angle = acos(sp_dot_d);
	//	vec3 diffuse_spot = SpotLight[i].Ld * Material.Kd * max(dot(L,Normal),0);
	//	vec3 spec_spot = SpotLight[i].Ls * Material.Ks * pow(max(dot(H,Normal), 0.0), Material.Shiness);
	//
	//	if (angle <= radians(SpotLight[i].Cutoff))
	//		finalColor = finalColor + spotEffect * SpotLight[i].La * (diffuse_spot + spec_spot);
	//}

	float shadow = ShadowCalculation(LightSpacePos);

	vec3 LightIntensity = ambient + finalColor;

	//FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    FragColor = vec4(LightIntensity, 1.0);
}
