#version 330 core

layout (location = 0) in vec3 vPosition;

layout (location = 1) in vec3 iOffset;
layout (location = 2) in float iScale;

void main()
{
	gl_Position = vec4((vPosition * iScale) + iOffset, 1);
}
