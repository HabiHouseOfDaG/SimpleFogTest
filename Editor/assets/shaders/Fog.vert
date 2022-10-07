#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

uniform mat4 u_Transform;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 vPos;

void main()
{
	vPos = u_View * u_Transform * vec4(a_Position, 1.0f);
	gl_Position = u_Projection * vPos;
}
