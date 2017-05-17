#version 440

in vec4 VertexPosition;
in vec3 VertexColor;

out vec4 Position;

uniform mat4 ModelViewMatrix;
uniform mat4 MVP;

out vec3 f_color;

void main()
{
	Position = ModelViewMatrix * VertexPosition;

   gl_Position = MVP * VertexPosition;
   f_color = VertexColor;
}