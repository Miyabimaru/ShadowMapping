#version 330 core
layout (location = 0) in vec4 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 texelCoords;

out vec4 Position;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix; 
uniform mat4 MVP;

void main()
{
    TexCoords = texelCoords;
	Position = ModelViewMatrix * VertexPosition;
	Normal =  NormalMatrix * VertexNormal;

	gl_Position = MVP * VertexPosition;
}