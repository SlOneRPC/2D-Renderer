#pragma once
#include "Demo.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../Shader.h"
#include "../Texture.h"

class TextureDemo : Demo
{
public:
	TextureDemo();
	~TextureDemo();

	void Init() override;
	void OnRender() override;
	void OnImguiRender() override;
	void Shutdown() override;

private:
	VertexBuffer* vertex;
	IndexBuffer* index;
	Shader* shader;
	Texture* texture;
};