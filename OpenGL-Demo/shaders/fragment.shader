#version 330 core

layout(location = 0) out vec4 colour;

uniform vec4 uColour;

void main()
{
	colour = uColour;
};