#version 400 core

in vec2 TexCoord;
out vec4 outColor;
uniform sampler2D uTexture;

void main()
{
	outColor = texture(uTexture, TexCoord);
}