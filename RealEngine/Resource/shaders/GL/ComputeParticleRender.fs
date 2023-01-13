#version 430 core

layout (location = 0) out vec4 color;

in float intensity;

void main(void)
{
	// 根据粒子的年龄, 在热红色和冷蓝色之间混合得到结果
	color = mix(vec4(0.0f, 0.2f, 1.0f, 1.0f), vec4(0.2f, 0.05f, 0.0f, 1.0f), intensity);
}