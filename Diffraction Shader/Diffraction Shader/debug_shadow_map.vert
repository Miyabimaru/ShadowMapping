#version 440
in vec4 vertexPosition;
in vec2 VertexTexCoord;

uniform mat4 MVP;

out vec2 TexCoords;

void main()
{
    TexCoords = VertexTexCoord;
    gl_Position = MVP * vertexPosition;
}
