#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 texCoords;
layout(location = 2) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

out vec4 v_Color;
out vec2 v_TexCoords;
out vec3 v_Normal;
out vec3 v_FragPos;

void main()
{
	gl_Position = u_Proj * u_View * u_Model * vec4(pos, 1.0f);

	v_Color = vec4(clamp(pos, 0.f, 1.f), 1.f);
	v_TexCoords = texCoords;
	v_Normal = mat3(transpose(inverse(u_Model))) * normal;
	v_FragPos = (u_Model * vec4(pos, 1.0f)).xyz;
}