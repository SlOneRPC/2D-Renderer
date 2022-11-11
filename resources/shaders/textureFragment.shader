#version 330 core

layout(location = 0) out vec4 colour;

in vec2 texCoord;

uniform vec4 uColour;
uniform sampler2D uTexture;

void main()
{
	colour = texture(uTexture, texCoord);
};