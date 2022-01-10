#version 400 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D Texture_Diffuse;

void main()
{
   FragColor = texture(Texture_Diffuse, TexCoords);
}