#version 330 core

in vec2 TexCoords;
in vec4 Position;
in vec3 Normal;

uniform vec4 LightPosition;
uniform vec3 LightIntensity;

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shiness;

out vec4 color;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main()
{
	vec3 L = normalize(vec3(LightPosition - Position));
	vec3 V = normalize(vec3(-Position));
	vec3 R = normalize(reflect(-L, Normal));

	vec3 ambient = LightIntensity * Ka;
	vec3 diffuse = LightIntensity * Kd * max(dot(L, Normal), 0.0);
	vec3 spec = LightIntensity * Ks * pow(max(dot(R, V), 0.0), Shiness);

	vec3 finalColor = diffuse + ambient;

	vec4 texColorDiffuse = texture(texture_diffuse1, TexCoords);
	vec4 texColorSpecular = texture(texture_specular1, TexCoords);
	vec4 texColor = mix(texColorDiffuse, texColorSpecular, texColorSpecular.a);

	color = (vec4(finalColor, 1.0) * texColor) + vec4(spec, 1.0);
}