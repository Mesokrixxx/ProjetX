#version 330 core

layout (location = 0) in vec3	vPos;
layout (location = 1) in vec3	vNormal;

layout (location = 2) in vec3	iPos;
layout (location = 3) in vec3	iScale;
layout (location = 4) in int	iColor;

flat out int color;

void	main() {
	color = iColor;

	gl_Position = vec4((vPos * iScale) + iPos, 1.0);
}
