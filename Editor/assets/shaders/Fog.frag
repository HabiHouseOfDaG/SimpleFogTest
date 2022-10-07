#version 460 core

in vec4 vPos;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec3 u_FogColor;
uniform float u_FogIntensity;

void main()
{
	float fogBegin = 0.1;
	float fogEnd = 50.0;
	float fogFactor = clamp((fogEnd - vPos.z) / (fogEnd - fogBegin) * u_FogIntensity, 0.0, 1.0);
	color = (1.0 - fogFactor) * u_Color + fogFactor * vec4(u_FogColor, 1.0);
}
