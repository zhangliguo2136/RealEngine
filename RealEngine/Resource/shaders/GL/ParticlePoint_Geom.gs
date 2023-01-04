#version 430 core

layout (points) in;
layout (points, max_vertices = 3) out;

out float alpha;

void main()
{
	gl_Position = vec4(gl_in[0].gl_Position.xyz + vec3(0.1f, 0.1f, 0.0f), 1.0);
	alpha = gl_in[0].gl_Position.w;
    EmitVertex();
	
	gl_Position = vec4(gl_in[0].gl_Position.xyz + vec3(0.0f, 0.1f, 0.0f), 1.0);
	alpha = gl_in[0].gl_Position.w;
    EmitVertex();
	
	gl_Position = vec4(gl_in[0].gl_Position.xyz + vec3(0.0f, 0.0f, 0.0f), 1.0);
	alpha = gl_in[0].gl_Position.w;
    EmitVertex();
}