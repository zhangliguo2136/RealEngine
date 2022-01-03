#version 400 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;

void main()
{
   TexCoords = inTexCoord;
   gl_Position = projection * view * model *  vec4(inPosition, 1.0);
   //gl_Position = vec4(inPosition, 1.0) * model * view * projection;
}