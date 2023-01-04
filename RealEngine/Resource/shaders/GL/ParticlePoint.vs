#version 430 core

layout (location = 0) in vec4 vertex;

uniform vec3 Offset;
uniform vec4 Color;

out vec2 TexCoords;
out vec4 ParticleColor;

void main()
{
    float scale = 0.1f;
    TexCoords = vertex.zw;
    ParticleColor = Color;
    gl_Position = vec4((vertex.xyz * scale) + Offset, 1.0);
}