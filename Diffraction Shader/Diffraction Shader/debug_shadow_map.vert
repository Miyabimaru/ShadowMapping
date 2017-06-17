#version 330 core
layout (location = 0) in vec4 vertexPosition;
layout (location = 2) in vec2 VertexTexCoord;

out vec2 TexCoords;

void main()
{
    TexCoords = VertexTexCoord;
    gl_Position = vertexPosition;
}
