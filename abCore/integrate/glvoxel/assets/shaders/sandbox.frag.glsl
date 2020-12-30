#version 450 core

//layout (location = 0) out vec4 o_Color;

in vec4 v_Color;
in vec2 v_TexCoord;
in float v_TexID;

out vec4 outColor;

uniform vec4 u_Color;
uniform int u_IsActive;

uniform sampler2D u_Textures[3];

void main()
{
	unsigned int texID = unsigned int(v_TexID);
	vec4 texColor;

	texColor = texture(u_Textures[texID], v_TexCoord);
	outColor = texColor;

	//outColor = v_Color;
}