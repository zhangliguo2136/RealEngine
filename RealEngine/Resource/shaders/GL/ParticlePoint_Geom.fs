#version 430 core

in float alpha;

out vec4 FragColor;

uniform sampler2D sprite;

void main()
{
    FragColor = texture(sprite, vec2(1.0, 1.0));
}