#version 430 core

layout (location = 0) in vec4 vertex;

uniform vec3 Offsets[512];
uniform vec4 Colors[512];

out vec2 TexCoords;
out vec4 ParticleColor;

void main()
{
    float scale = 0.1f;
    TexCoords = vertex.zw;
    ParticleColor = Colors[gl_InstanceID];
    gl_Position = vec4((vertex.xyz * scale) + Offsets[gl_InstanceID], 1.0);
}