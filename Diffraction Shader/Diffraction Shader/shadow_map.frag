#version 330 core
out vec4 FragColor;
  
in vec2 VertexTexCoord;

uniform sampler2D depthMap;

void main()
{             
    float depthValue = texture(depthMap, VertexTexCoord).r;
    FragColor = vec4(vec3(depthValue), 1.0);
} 