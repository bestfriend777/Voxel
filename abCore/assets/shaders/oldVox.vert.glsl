#version 450 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoord;
layout (location = 3) in float a_TexID;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexID;

uniform mat4 u_Model;
uniform mat4 u_Transform;	
uniform mat4 u_View;
uniform mat4 u_Projection;

//mvp is calculated in reverse order in glsl

void main()
{
	gl_Position = u_Projection * u_View * u_Transform * u_Model * vec4(a_Position, 1.0f);
	
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_TexID = a_TexID;

}