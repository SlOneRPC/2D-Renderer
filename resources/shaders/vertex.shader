#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 textureCoord;

out vec2 texCoord;

uniform mat4 uTransform;
uniform mat4 uViewProjection;

void main()
{
	texCoord = textureCoord;
	gl_Position = uViewProjection * uTransform * vec4(position, 0.0, 1.0);
};