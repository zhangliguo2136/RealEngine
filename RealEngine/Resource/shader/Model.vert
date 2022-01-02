#version 400 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

uniform mat4 uWorldTransform;
uniform mat4 uViewProj;

out vec2 TexCoords;

void main()
{
   TexCoords = inTexCoord;
   vec4 pos = vec4(inPosition, 1.0);
   gl_Position = pos * uWorldTransform * uViewProj;
}