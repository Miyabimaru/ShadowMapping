#version 440

in vec3 f_color;
in vec4 Position;

uniform vec3 fogColor;
uniform float maxDist;
uniform float minDist;

out vec4 FragColors;

void main()
{
   FragColors = vec4(f_color,1.0);
}