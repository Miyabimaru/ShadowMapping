#version 330 core
layout (location = 0) in vec4 VertexPosition;
layout (location = 1) in vec2 VertexTexCoords;

out vec2 TexCoords;

void main()
{
    TexCoords = VertexTexCoords;
    gl_Position = VertexPosition;
}