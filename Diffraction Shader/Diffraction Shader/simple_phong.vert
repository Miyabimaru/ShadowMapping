#version 440

in vec4 vertexPosition;
in vec3 vertexNormalTRUC;
in vec3 VertexTexCoord; 

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

// Uniform values
uniform LightInfo PointLights[5];
uniform MaterialInfo Material;

uniform mat4 MVP;
uniform mat3 normalMatrix; 
uniform mat4 ModelViewMatrix;

out vec4 Position;
out vec3 Normal;

void main()
{
	vec3 N = normalize( normalMatrix * vertexNormalTRUC);
	vec4 P = ModelViewMatrix * vertexPosition;
	
	Position = P;
	Normal = N;

	gl_Position = MVP * vertexPosition;
}
