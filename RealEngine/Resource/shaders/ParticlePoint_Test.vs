#version 430 core

layout (location = 0) in vec4 vertex;

out vec2 TexCoords;

void main()
{
	TexCoords = vertex.zw;
    gl_Position = vec4(vertex.xy * 0.1, 1.0, 1.0);
}